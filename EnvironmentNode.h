//
// Created by voxed on 3/28/22.
//

#ifndef VXBLAZE_ENVIRONMENTNODE_H
#define VXBLAZE_ENVIRONMENTNODE_H


#include <memory>
#include "Node.h"

namespace Vx::Blaze {

    class Texture;

    class EnvironmentNode : public Node {

    public:
        std::shared_ptr<Vx::Blaze::Texture> Texture;
        std::shared_ptr<Node> Content;

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;
    };

}


#endif //VXBLAZE_ENVIRONMENTNODE_H
