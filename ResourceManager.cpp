//
// Created by voxed on 3/23/22.
//

#include "ResourceManager.h"
#include "ShaderManager.h"

namespace Vx::Blaze {

    ResourceManager::ResourceManager() {
        ShaderManager = std::make_shared<Vx::Blaze::ShaderManager>();
    }

}