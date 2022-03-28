//
// Created by voxed on 3/28/22.
//

#include "EnvironmentNode.h"
#include "NodeVisitor.h"

namespace Vx::Blaze {

    void EnvironmentNode::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<EnvironmentNode>(self), visitor);
    }

}
