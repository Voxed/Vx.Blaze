//
// Created by voxed on 3/28/22.
//

#ifndef VXBLAZE_ENVIRONMENTMAP_H
#define VXBLAZE_ENVIRONMENTMAP_H


#include <memory>

namespace Vx::Blaze {

    class Texture;

    class EnvironmentMap {
    public:
        const std::shared_ptr<Vx::Blaze::Texture> Texture;
        const std::shared_ptr<Vx::Blaze::Texture> IrradianceMap;
        const std::shared_ptr<Vx::Blaze::Texture> ReflectionMap;

        explicit EnvironmentMap(std::shared_ptr<Vx::Blaze::Texture> environmentMap);
    };

}

#endif //VXBLAZE_ENVIRONMENTMAP_H
