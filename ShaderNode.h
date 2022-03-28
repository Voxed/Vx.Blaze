//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_SHADERNODE_H
#define VXBLAZE_SHADERNODE_H

#include <GL/glew.h>
#include "Node.h"

namespace Vx::Blaze {

    class Shader;

    class ShaderNode : public Node {
    public:
        std::shared_ptr<Node> Content;
        std::shared_ptr<Vx::Blaze::Shader> Shader;
        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;
    };

}


#endif //VXBLAZE_SHADERNODE_H
