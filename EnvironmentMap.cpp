//
// Created by voxed on 3/28/22.
//

#include "EnvironmentMap.h"
#include "Texture.h"
#include "Geometry.h"

namespace Vx::Blaze {

    EnvironmentMap::EnvironmentMap(std::shared_ptr<Vx::Blaze::Texture> environmentMap)
            : Texture(environmentMap), IrradianceMap(std::make_shared<Vx::Blaze::Texture>()),
              ReflectionMap(std::make_shared<Vx::Blaze::Texture>()) {
        std::shared_ptr<Geometry> fullscreenQuad = std::make_shared<Geometry>(
                std::vector<glm::vec3>{
                        {-1.0f, -1.0f, 0.0f},
                        {1.0f,  -1.0f, 0.0f},
                        {1.0f,  1.0f,  0.0f},
                        {-1.0f, 1.0f,  0.0f}
                },
                std::vector<unsigned int>{
                        0, 1, 3,
                        1, 2, 3
                }
        );
        std::shared_ptr<Shader> shader;

        fullscreenQuad->Render(nullptr, shader, glm::mat4(1.0f));
    }

}