//
// Created by voxed on 3/23/22.
//

#include "ShaderNode.h"

#include "NodeVisitor.h"

namespace Vx::Blaze {

    void ShaderNode::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<ShaderNode>(self), visitor);
    }

}
