//
// Created by voxed on 3/24/22.
//

#ifndef VXBLAZEGLTF_GLTFLOADER_H
#define VXBLAZEGLTF_GLTFLOADER_H

#include <filesystem>
#include "ThirdParty/tiny_gltf.h"
#include "Node.h"

namespace Vx::Blaze::GLTF {

    class GLTFLoader {
        std::shared_ptr<Node> loadScene(tinygltf::Scene scene, tinygltf::Model context);
        std::shared_ptr<Node> loadNode(tinygltf::Node scene, tinygltf::Model context);
        std::shared_ptr<Node> loadMesh(tinygltf::Mesh scene, tinygltf::Model context);

    public:
        std::shared_ptr<Node> Load(std::string path);
    };

}

#endif //VXBLAZEGLTF_GLTFLOADER_H
