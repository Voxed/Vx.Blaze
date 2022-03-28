//
// Created by voxed on 3/28/22.
//

#include <vector>
#include "BackgroundNode.h"
#include "NodeVisitor.h"
#include "Geometry.h"
#include "Texture.h"

namespace Vx::Blaze {

    void BackgroundNode::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<BackgroundNode>(self), visitor);
    }

    void BackgroundNode::Render(std::shared_ptr<Camera> camera) {
        Shader->Use();
        Shader->SetUniform("PV", glm::inverse(camera->Projection * camera->View));
        Shader->SetUniform("CAMERA_POSITION", glm::vec3(0));
        Shader->SetUniform("MULTIPLIER", 1.0f);
        Texture->Bind(GL_TEXTURE6);

        glDisable(GL_DEPTH_TEST);
        fullscreenQuad->Render(nullptr, Shader, glm::mat4(1.0f));
        glEnable(GL_DEPTH_TEST);
    }

    BackgroundNode::BackgroundNode() {
        fullscreenQuad = std::make_shared<Vx::Blaze::Geometry>(
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
    }

}
