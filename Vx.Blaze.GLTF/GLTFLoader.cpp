//
// Created by voxed on 3/24/22.
//

#include "GLTFLoader.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "ThirdParty/tiny_gltf.h"
#include "Group.h"
#include "TransformNode.h"
#include "Geometry.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Buffer.h"
#include "BufferView.h"
#include "Accessor.h"
#include "Material.h"

namespace Vx::Blaze::GLTF {

    std::shared_ptr<Node> GLTF::GLTFLoader::Load(std::string path) {
        printf("wooow\n");

        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);

        printf("%s\n", model.nodes[model.scenes[0].nodes[0]].name.c_str());

        return loadScene(model.scenes[0], model);
    }

    std::shared_ptr<Node> GLTFLoader::loadScene(tinygltf::Scene scene, tinygltf::Model context) {
        std::shared_ptr<Group> group = std::make_shared<Group>();

        for (const auto &item: scene.nodes) {
            group->Children.push_back(loadNode(context.nodes[item], context));
        }

        return group;
    }

    std::shared_ptr<Node> GLTFLoader::loadNode(tinygltf::Node node, tinygltf::Model context) {
        std::shared_ptr<Group> current = std::make_shared<Group>();
        std::shared_ptr<TransformNode> root = std::make_shared<TransformNode>();
        root->Content = current;

        if (!node.matrix.empty()) {
            root->Transform = glm::make_mat4(node.matrix.data());
        } else {
            root->Transform = glm::mat4(1.0);
            if (!node.translation.empty()) {
                root->Transform = root->Transform * glm::translate(glm::mat4(1.0),
                                                                   glm::vec3(node.translation[0], node.translation[1],
                                                                             node.translation[2]));
            }
            if (!node.rotation.empty()) {
                root->Transform = root->Transform * glm::toMat4(
                        glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]));
            }
            if (!node.scale.empty()) {
                root->Transform = root->Transform *
                                  glm::scale(glm::mat4(1.0), glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
            }
        }

        for (const auto &item: node.children) {
            current->Children.push_back(loadNode(context.nodes[item], context));
        }

        if (node.mesh >= 0) {
            current->Children.push_back(loadMesh(context.meshes[node.mesh], context));
        }

        return root;

    }

    std::shared_ptr<Node> GLTFLoader::loadMesh(tinygltf::Mesh mesh, tinygltf::Model context) {
        std::shared_ptr<Group> root = std::make_shared<Group>();
        for (const auto &item: mesh.primitives) {
            std::map<std::string, std::shared_ptr<Accessor>> attributes;
            if(!accessors.contains(item.indices)){
                accessors[item.indices] = loadAccessor(context.accessors[item.indices], context);
            }
            std::shared_ptr<Accessor> indices = accessors[item.indices];
            for (const auto &item: item.attributes) {
                if(!accessors.contains(item.second)){
                    accessors[item.second] = loadAccessor(context.accessors[item.second], context);
                }
                attributes[item.first] = accessors[item.second];
            }

            if(!materials.contains(item.material)) {
                materials[item.material] = loadMaterial(context.materials[item.material], context);
            }
            std::shared_ptr<Material> material = materials[item.material];

            std::shared_ptr<Geometry> geo = std::make_shared<Geometry>(
                    attributes,
                    indices,
                    material
            );
            root->Children.push_back(geo);
        }
        return root;
    }

    std::shared_ptr<Vx::Blaze::Buffer<void>> GLTFLoader::loadBuffer(tinygltf::Buffer buffer, tinygltf::Model context) {

        return std::make_shared<Buffer<unsigned char>>(buffer.data);
    }

    std::shared_ptr<Vx::Blaze::BufferView>
    GLTFLoader::loadBufferView(tinygltf::BufferView bufferView, tinygltf::Model context) {
        if (!buffers.contains(bufferView.buffer)) {
            buffers[bufferView.buffer] = loadBuffer(context.buffers[bufferView.buffer], context);
        }

        return std::make_shared<BufferView>(buffers[bufferView.buffer], bufferView.byteLength,
                                            bufferView.byteStride,
                                            (const void *) bufferView.byteOffset);
    }

    std::shared_ptr<Vx::Blaze::Accessor>
    GLTFLoader::loadAccessor(tinygltf::Accessor accessor, tinygltf::Model context) {
        if (!bufferViews.contains(accessor.bufferView)) {
            bufferViews[accessor.bufferView] = loadBufferView(context.bufferViews[accessor.bufferView], context);
        }

        GLsizei componentCount;
        switch (accessor.type) {
            case TINYGLTF_TYPE_SCALAR:
                componentCount = 1;
                break;
            case TINYGLTF_TYPE_VEC2:
                componentCount = 2;
                break;
            case TINYGLTF_TYPE_VEC3:
                componentCount = 3;
                break;
            case TINYGLTF_TYPE_VEC4:
                componentCount = 4;
                break;
        }

        GLenum componentType;
        switch (accessor.componentType) {
            case TINYGLTF_COMPONENT_TYPE_BYTE:
                componentType = GL_BYTE;
                break;
            case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                componentType = GL_DOUBLE;
                break;
            case TINYGLTF_COMPONENT_TYPE_FLOAT:
                componentType = GL_FLOAT;
                break;
            case TINYGLTF_COMPONENT_TYPE_INT:
                componentType = GL_INT;
                break;
            case TINYGLTF_COMPONENT_TYPE_SHORT:
                componentType = GL_SHORT;
                break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                componentType = GL_UNSIGNED_BYTE;
                break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                componentType = GL_UNSIGNED_INT;
                break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                componentType = GL_UNSIGNED_SHORT;
                break;
        }

        return std::make_shared<Accessor>(bufferViews[accessor.bufferView], componentCount, componentType,
                                          accessor.count);
    }

    std::shared_ptr<Vx::Blaze::Material>
    GLTFLoader::loadMaterial(tinygltf::Material material, tinygltf::Model context) {
        std::vector<double> c = material.pbrMetallicRoughness.baseColorFactor;
        glm::vec4 color = glm::vec4(c[0], c[1], c[2], c[3]);
        float metallic = material.pbrMetallicRoughness.metallicFactor;
        float roughness = material.pbrMetallicRoughness.roughnessFactor;

        std::shared_ptr<Material> m = std::make_shared<Material>(color, metallic, roughness);

        return m;
    }

}
