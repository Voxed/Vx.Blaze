//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_RESOURCEMANAGER_H
#define VXBLAZE_RESOURCEMANAGER_H

#include <memory>

namespace Vx::Blaze {
    class ShaderManager;

    class ResourceManager {
    public:
        ResourceManager();
        std::shared_ptr<Vx::Blaze::ShaderManager> ShaderManager;
    };

}

#endif //VXBLAZE_RESOURCEMANAGER_H
