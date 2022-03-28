//
// Created by voxed on 3/25/22.
//

#include <cstdio>
#include "Material.h"

namespace Vx::Blaze {

    Material::Material(glm::vec4 color, float metallic, float roughness) :
            Color(color), Metallic(metallic), Roughness(roughness) {

        printf("ROUGHNESS: %f\n", roughness);
    }

}
