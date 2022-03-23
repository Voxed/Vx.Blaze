//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_TRANSFORMNODE_H
#define VXBLAZE_TRANSFORMNODE_H


#include "Node.h"
#include <glm/glm.hpp>

namespace Vx::Blaze {

    class TransformNode : public Node {
    public:
        std::shared_ptr<Node> Content;
        glm::mat4 Transform;

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;
    };

}


#endif //VXBLAZE_TRANSFORMNODE_H
