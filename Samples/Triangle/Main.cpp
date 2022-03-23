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

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <chrono>

int main() {

    glfwInit();

    GLFWwindow *window = glfwCreateWindow(640, 480, "", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = 1;
    glewInit();

    std::vector<glm::vec3> vertices = {};
    std::vector<glm::vec3> normals = {};

    objl::Loader Loader;
    bool loadout = Loader.LoadFile("assets/suzanne.obj");
    objl::Mesh curMesh = Loader.LoadedMeshes[0];
    for (const auto &item : curMesh.Vertices) {
        vertices.emplace_back(item.Position.X, item.Position.Y, item.Position.Z);
        normals.emplace_back(item.Normal.X, item.Normal.Y, item.Normal.Z);
    }



    std::vector<unsigned int> indices = curMesh.Indices;

    std::shared_ptr<Vx::Blaze::ResourceManager> rm = std::make_shared<Vx::Blaze::ResourceManager>();

    std::shared_ptr<Vx::Blaze::ShaderNode> root = std::make_shared<Vx::Blaze::ShaderNode>(); //std::make_shared<Vx::Blaze::Geometry>(vertices, indices, rm);
    std::shared_ptr<Vx::Blaze::Camera> cam = std::make_shared<Vx::Blaze::Camera>();
    std::shared_ptr<Vx::Blaze::Group> group = std::make_shared<Vx::Blaze::Group>();
    std::shared_ptr<Vx::Blaze::Geometry> geo = std::make_shared<Vx::Blaze::Geometry>(vertices, normals, indices);
    std::shared_ptr<Vx::Blaze::TransformNode> tr = std::make_shared<Vx::Blaze::TransformNode>();
    std::shared_ptr<Vx::Blaze::TransformNode> tr2 = std::make_shared<Vx::Blaze::TransformNode>();
    std::shared_ptr<Vx::Blaze::TransformNode> tr3 = std::make_shared<Vx::Blaze::TransformNode>();

    std::shared_ptr<Vx::Blaze::TransformNode> s1 = std::make_shared<Vx::Blaze::TransformNode>();
    std::shared_ptr<Vx::Blaze::TransformNode> s2 = std::make_shared<Vx::Blaze::TransformNode>();
    std::shared_ptr<Vx::Blaze::TransformNode> s3 = std::make_shared<Vx::Blaze::TransformNode>();

    s1->Transform = glm::scale(glm::mat4(1.0f), {0.5f, 0.5f, 0.5f});
    s2->Transform = s1->Transform;
    s3->Transform = s1->Transform;

    s1->Content = geo;
    s2->Content = geo;
    s3->Content = geo;

    root->Shader = rm->ShaderManager->Get("assets/shaders/pbr");
    root->Content = cam;
    cam->Content = tr;
    tr->Content = group;
    tr->Transform = glm::rotate(glm::mat4(1.f), 1.0f, {1.f, 0.f, 0.f});
    group->Children.push_back(s1);
    s2->Content = tr2;
    tr2->Content = geo;
    tr2->Transform = glm::translate(glm::mat4(1.0f), {1.f, 0.f, 0.f});
    group->Children.push_back(s2);

    s3->Content = tr3;
    tr3->Content = geo;
    tr3->Transform = glm::translate(glm::mat4(1.0f), {-1.f, 0.f, 0.f});
    group->Children.push_back(s3);

    cam->Projection = glm::perspective(45.0f, 640.f / 480.f, 0.01f, 150.0f);
    cam->View = glm::lookAt<float, glm::defaultp>(
            {0.0f, 0.0f, 2.0f},
            {0.f, 0.f, 0.f},
            {0.0f, 1.0f, 0.0f});
    //cam->Projection = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));

    auto startTime = std::chrono::system_clock::now();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        long millis = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime)).count();
        tr->Transform = glm::rotate(glm::mat4(1.f), ((float)millis)/1000.f, {1.f, 0.f, 0.f});
        /*cam->View = glm::lookAt<float, glm::defaultp>(
                {cosf(((float)millis)/1000.f)*2.0f, 0.0f, sinf(((float)millis)/1000.f)*2.0f},
                {0.f, 0.f, 0.f},
                {0.0f, 1.0f, 0.0f});*/
        root->Visit(std::make_shared<Vx::Blaze::OGLVisitor>(), root);
        glfwSwapBuffers(window);
    }
}