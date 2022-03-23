//
// Created by voxed on 3/23/22.
//

#include "Camera.h"
#include "NodeVisitor.h"

namespace Vx::Blaze {

    void Camera::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<Camera>(self), visitor);
    }

}