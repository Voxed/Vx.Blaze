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
        std::shared_ptr<Group> root = current;

        if (!node.translation.empty()) {
            auto transform = std::make_shared<TransformNode>();
            current = std::make_shared<Group>();
            transform->Transform = glm::translate(glm::mat4(1.0f), glm::vec3(node.translation[0], node.translation[1],
                                                                             node.translation[2]));
            transform->Content = current;
            root->Children.push_back(transform);
        }

        for (const auto &item : node.children) {
            current->Children.push_back(loadNode(context.nodes[item], context));
        }

        if(node.mesh >= 0) {
            current->Children.push_back(loadMesh(context.meshes[node.mesh], context));
        }

        return root;

    }

    std::shared_ptr<Node> GLTFLoader::loadMesh(tinygltf::Mesh mesh, tinygltf::Model context) {
        std::shared_ptr<Group> root = std::make_shared<Group>();
        for (const auto &item : mesh.primitives) {
            auto attributes = item.attributes;
            if(attributes.contains("POSITION") && attributes.contains("NORMAL")) {
                auto p = context.bufferViews[context.accessors[attributes["POSITION"]].bufferView];
                auto n = context.bufferViews[context.accessors[attributes["NORMAL"]].bufferView];
                auto i = context.bufferViews[context.accessors[item.indices].bufferView];

                if(p.buffer == n.buffer && p.buffer == i.buffer) {
                    auto buffer = context.buffers[n.buffer];
                    std::shared_ptr<Geometry> geo = std::make_shared<Geometry>(
                        p.byteOffset, p.byteLength,
                        n.byteOffset, n.byteLength,
                        buffer.data,
                        i.byteOffset,
                        context.accessors[item.indices].count
                    );
                    root->Children.push_back(geo);
                }
            }
        }
        return root;
    }

}
