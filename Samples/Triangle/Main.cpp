//
// Created by voxed on 3/23/22.
//

#include <memory>
#include "Node.h"
#include "Geometry.h"
#include "OGLVisitor.h"
#include "ResourceManager.h"
#include "Group.h"
#include "Camera.h"
#include "ShaderNode.h"
#include "ShaderManager.h"
#include "TransformNode.h"
#include "Samples/Triangle/ThirdParty/OBJ_Loader.h"
#include "Vx.Blaze.GLTF/GLTFLoader.h"
#include "Accessor.h"
#include "Buffer.h"
#include "BufferView.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <chrono>
#include "ThirdParty/stb_image.h"
#include "Texture.h"
#include "BackgroundNode.h"
#include "EnvironmentNode.h"

int main() {

    glfwInit();

    GLFWwindow *window = glfwCreateWindow(640, 480, "", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = 1;
    glewInit();

    std::vector<glm::vec3> vertices = {};
    std::vector<glm::vec3> normals = {};
    std::vector<glm::vec3> vertices2 = {};
    std::vector<glm::vec3> normals2 = {};

    objl::Loader Loader;
    bool loadout = Loader.LoadFile("assets/suzanne.obj");
    objl::Mesh curMesh = Loader.LoadedMeshes[0];
    for (const auto &item: curMesh.Vertices) {
        vertices.emplace_back(item.Position.X, item.Position.Y, item.Position.Z);
        normals.emplace_back(item.Normal.X, item.Normal.Y, item.Normal.Z);
    }
    std::vector<unsigned int> indices = curMesh.Indices;

    loadout = Loader.LoadFile("assets/teapot.obj");
    curMesh = Loader.LoadedMeshes[0];
    for (const auto &item: curMesh.Vertices) {
        vertices2.emplace_back(item.Position.X, item.Position.Y, item.Position.Z);
        normals2.emplace_back(item.Normal.X, item.Normal.Y, item.Normal.Z);
    }


    std::vector<unsigned int> indices2 = curMesh.Indices;

    std::shared_ptr<Vx::Blaze::ResourceManager> rm = std::make_shared<Vx::Blaze::ResourceManager>();

    std::shared_ptr<Vx::Blaze::ShaderNode> root = std::make_shared<Vx::Blaze::ShaderNode>(); //std::make_shared<Vx::Blaze::Geometry>(vertices, indices, rm);
    std::shared_ptr<Vx::Blaze::Camera> cam = std::make_shared<Vx::Blaze::Camera>();
    std::shared_ptr<Vx::Blaze::BackgroundNode> bg = std::make_shared<Vx::Blaze::BackgroundNode>();
    std::shared_ptr<Vx::Blaze::EnvironmentNode> env = std::make_shared<Vx::Blaze::EnvironmentNode>();
    std::shared_ptr<Vx::Blaze::Group> group = std::make_shared<Vx::Blaze::Group>();

    std::shared_ptr<Vx::Blaze::TransformNode> tr = std::make_shared<Vx::Blaze::TransformNode>();

    root->Shader = rm->ShaderManager->Get("assets/shaders/pbr");
    root->Content = cam;
    cam->Content = bg;
    bg->Content = env;
    env->Content = tr;
    tr->Content = group;
    tr->Transform = glm::rotate(glm::mat4(1.f), 0.0f, {1.f, 0.f, 0.f});

    cam->Projection = glm::perspective(45.0f, 640.f / 480.f, 0.01f, 150.0f);
    cam->View = glm::lookAt<float, glm::defaultp>(
            {0.0f, 0.0f, 5.0f},
            {0.f, 0.f, 0.f},
            {0.0f, 1.0f, 0.0f});
    //cam->Projection = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));

    Vx::Blaze::GLTF::GLTFLoader gltfLoader;

    auto node = gltfLoader.Load("assets/test.gltf");
    group->Children.push_back(node);

    auto startTime = std::chrono::system_clock::now();

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, &cam);


    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        std::shared_ptr<Vx::Blaze::Camera> cam = *(std::shared_ptr<Vx::Blaze::Camera> *) glfwGetWindowUserPointer(
                window);
        cam->Projection = glm::perspective(45.0f, ((float) width) / ((float) height), 0.01f, 150.0f);
    });



    auto shader = rm->ShaderManager->Get("assets/shaders/sky");

    int width, height, components;
    float *data = nullptr;

    stbi_set_flip_vertically_on_load(false);
    data = stbi_loadf("assets/sky.hdr", &width, &height, &components, 3);
    stbi_set_flip_vertically_on_load(true);

    if (data == NULL) {
        std::cout << "Failed to load image: " << "asdfasd" << ".\n";
        exit(1);
    }

    auto d = std::vector<float>(data, &data[height*width*3]);

    auto t = std::make_shared<Vx::Blaze::Texture>(
            d,
            width, height,
            GL_RGB32F, GL_RGB
    );

    bg->Texture = t;
    bg->Shader = shader;

    env->Texture = t;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        //fullscreenQuad->Render(nullptr, shader, glm::mat4(1.0f));
        glEnable(GL_DEPTH_TEST);

        long millis = (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - startTime)).count();
        cam->View = glm::lookAt<float, glm::defaultp>(
                {cosf(((float) millis) / 1000.f) * 3.0f, 0.0f, 8.0f},
                {0.f, 0.f, 0.f},
                {0.0f, 1.0f, 0.0f});
        root->Visit(std::make_shared<Vx::Blaze::OGLVisitor>(), root);
        glfwSwapBuffers(window);
    }
}