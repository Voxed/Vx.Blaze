//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_CAMERA_H
#define VXBLAZE_CAMERA_H

#include "glm/glm.hpp"
#include "Node.h"

namespace Vx::Blaze {

    class Camera : public Node {
    public:
        glm::mat4 Projection = glm::mat4(1.0);
        glm::mat4 View = glm::mat4(1.0);
        std::shared_ptr<Node> Content;

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;
    };

}


#endif //VXBLAZE_CAMERA_H
