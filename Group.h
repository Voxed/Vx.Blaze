//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_GROUP_H
#define VXBLAZE_GROUP_H

#include <vector>
#include <memory>
#include "Node.h"

namespace Vx::Blaze {

    class Group : public Node {
    public:
        std::vector<std::shared_ptr<Node>> Children;

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;
    };

}


#endif //VXBLAZE_GROUP_H
