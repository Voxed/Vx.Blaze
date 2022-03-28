//
// Created by voxed on 3/24/22.
//

#ifndef VXBLAZEGLTF_GLTFLOADER_H
#define VXBLAZEGLTF_GLTFLOADER_H

#include <filesystem>
#include "ThirdParty/tiny_gltf.h"
#include "Node.h"

namespace Vx::Blaze {
    class Accessor;

    class BufferView;

    template <typename T>
    class Buffer;

    class Material;

    namespace GLTF {

        class GLTFLoader {
            std::shared_ptr<Node> loadScene(tinygltf::Scene scene, tinygltf::Model context);

            std::shared_ptr<Node> loadNode(tinygltf::Node scene, tinygltf::Model context);

            std::shared_ptr<Node> loadMesh(tinygltf::Mesh scene, tinygltf::Model context);

            std::shared_ptr<Vx::Blaze::Accessor> loadAccessor(tinygltf::Accessor accessor, tinygltf::Model context);

            std::shared_ptr<Vx::Blaze::Material> loadMaterial(tinygltf::Material accessor, tinygltf::Model context);

            std::shared_ptr<Vx::Blaze::BufferView>
            loadBufferView(tinygltf::BufferView bufferView, tinygltf::Model context);

            std::shared_ptr<Vx::Blaze::Buffer<void>> loadBuffer(tinygltf::Buffer buffer, tinygltf::Model context);

            std::map<int, std::shared_ptr<Accessor>>
                    accessors;
            std::map<int, std::shared_ptr<BufferView>> bufferViews;
            std::map<int, std::shared_ptr<Buffer<void>>> buffers;
            std::map<int, std::shared_ptr<Material>> materials;

        public:
            std::shared_ptr<Node> Load(std::string path);
        };

    }

}

#endif //VXBLAZEGLTF_GLTFLOADER_H
