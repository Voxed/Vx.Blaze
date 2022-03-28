//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_NODEVISITOR_H
#define VXBLAZE_NODEVISITOR_H

#include <memory>

namespace Vx::Blaze {

    class Geometry;
    class Camera;
    class Group;
    class ShaderNode;
    class TransformNode;
    class BackgroundNode;
    class EnvironmentNode;

    class NodeVisitor {
    public:
        virtual void Accept(std::shared_ptr<Geometry> geometry, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<Camera> camera, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<Group> group, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<ShaderNode> shader, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<TransformNode> shader, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<BackgroundNode> env, std::shared_ptr<NodeVisitor> self) = 0;
        virtual void Accept(std::shared_ptr<EnvironmentNode> env, std::shared_ptr<NodeVisitor> self) = 0;
    };

}

#endif //VXBLAZE_NODEVISITOR_H
