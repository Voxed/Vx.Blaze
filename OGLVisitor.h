//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_OGLVISITOR_H
#define VXBLAZE_OGLVISITOR_H


#include "NodeVisitor.h"
#include <glm/glm.hpp>

namespace Vx::Blaze {

    class Shader;

    class OGLVisitor : public NodeVisitor {
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<EnvironmentNode> environment;
        glm::mat4 transform = glm::mat4(1.0f);

        std::shared_ptr<OGLVisitor> applyCamera(std::shared_ptr<Camera> camera);
        std::shared_ptr<OGLVisitor> applyShader(std::shared_ptr<ShaderNode> shader) ;
        std::shared_ptr<OGLVisitor> applyTransform(std::shared_ptr<TransformNode> transform);
        std::shared_ptr<OGLVisitor> applyEnvironment(std::shared_ptr<EnvironmentNode> env);

    public:
        void Accept(std::shared_ptr<Geometry> geometry, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<Camera> camera, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<Group> group, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<ShaderNode> shader, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<TransformNode> transform, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<BackgroundNode> env, std::shared_ptr<NodeVisitor> self) override;
        void Accept(std::shared_ptr<EnvironmentNode> env, std::shared_ptr<NodeVisitor> self) override;
    };

}


#endif //VXBLAZE_OGLVISITOR_H
