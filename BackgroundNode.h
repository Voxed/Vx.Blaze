//
// Created by voxed on 3/28/22.
//

#ifndef VXBLAZE_BACKGROUNDNODE_H
#define VXBLAZE_BACKGROUNDNODE_H

#include <memory>
#include "Shader.h"
#include "Node.h"
#include "Camera.h"

namespace Vx::Blaze {

    class Texture;
    class Geometry;

    class BackgroundNode : public Node {

        std::shared_ptr<Geometry> fullscreenQuad;

    public:
        std::shared_ptr<Vx::Blaze::Shader> Shader;
        std::shared_ptr<Vx::Blaze::Texture> Texture;
        std::shared_ptr<Node> Content;

        BackgroundNode();

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;

        void Render(std::shared_ptr<Camera> camera);
    };

}

#endif //VXBLAZE_BACKGROUNDNODE_H
