//
// Created by voxed on 3/25/22.
//

#ifndef VXBLAZE_MATERIAL_H
#define VXBLAZE_MATERIAL_H

#include <glm/glm.hpp>

namespace Vx::Blaze {

    class Material {
    public:
        const glm::vec4 Color;
        const float Metallic;
        const float Roughness;
        Material(glm::vec4 color, float metallic, float roughness);
    };

}

#endif //VXBLAZE_MATERIAL_H
