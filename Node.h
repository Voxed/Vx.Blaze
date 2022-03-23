//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_NODE_H
#define VXBLAZE_NODE_H

#include <memory>

namespace Vx::Blaze {

    class NodeVisitor;

    class Node {
    public:
        virtual void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) = 0;
    };

}

#endif //VXBLAZE_NODE_H
