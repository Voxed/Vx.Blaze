//
// Created by voxed on 3/23/22.
//

#include <iostream>
#include "OGLVisitor.h"
#include "Geometry.h"
#include "Camera.h"
#include "Group.h"
#include "ShaderNode.h"
#include "TransformNode.h"
#include <glm/ext.hpp>
#include "BackgroundNode.h"
#include "EnvironmentNode.h"

namespace Vx::Blaze {

    std::shared_ptr<OGLVisitor> OGLVisitor::applyCamera(std::shared_ptr<Camera> camera) {
        auto visitor = std::make_shared<OGLVisitor>();
        visitor->camera = camera;
        visitor->shader = shader;
        visitor->transform = transform;
        return visitor;
    }

    std::shared_ptr<OGLVisitor> OGLVisitor::applyShader(std::shared_ptr<ShaderNode> shader) {
        auto visitor = std::make_shared<OGLVisitor>();
        visitor->camera = camera;
        visitor->shader = shader->Shader;
        visitor->transform = transform;
        visitor->environment = environment;
        return visitor;
    }

    std::shared_ptr<OGLVisitor> OGLVisitor::applyTransform(std::shared_ptr<TransformNode> transform) {
        auto visitor = std::make_shared<OGLVisitor>();
        visitor->camera = camera;
        visitor->shader = shader;
        visitor->environment = environment;
        visitor->transform = this->transform * transform->Transform;
        return visitor;
    }

    std::shared_ptr<OGLVisitor> OGLVisitor::applyEnvironment(std::shared_ptr<EnvironmentNode> env) {
        auto visitor = std::make_shared<OGLVisitor>();
        visitor->camera = camera;
        visitor->shader = shader;
        visitor->transform = transform;
        visitor->environment = env;
        return visitor;
    }

    void OGLVisitor::Accept(std::shared_ptr<Geometry> geometry, std::shared_ptr<NodeVisitor> self) {
        geometry->Render(camera, shader, transform, environment);
    }

    void OGLVisitor::Accept(std::shared_ptr<Camera> camera, std::shared_ptr<NodeVisitor> self) {
        camera->Content->Visit(applyCamera(camera), camera->Content);
    }

    void OGLVisitor::Accept(std::shared_ptr<Group> group, std::shared_ptr<NodeVisitor> self) {
        for (const auto &item: group->Children) {
            item->Visit(self, item);
        }
    }

    void OGLVisitor::Accept(std::shared_ptr<ShaderNode> shader, std::shared_ptr<NodeVisitor> self) {
        shader->Content->Visit(applyShader(shader), shader->Content);
    }

    void OGLVisitor::Accept(std::shared_ptr<TransformNode> transform, std::shared_ptr<NodeVisitor> self) {
        transform->Content->Visit(applyTransform(transform), transform->Content);
    }

    void OGLVisitor::Accept(std::shared_ptr<BackgroundNode> env, std::shared_ptr<NodeVisitor> self) {
        env->Render(camera);
        env->Content->Visit(self, env->Content);
    }

    void OGLVisitor::Accept(std::shared_ptr<EnvironmentNode> env, std::shared_ptr<NodeVisitor> self) {
        env->Content->Visit(applyEnvironment(env), env->Content);
    }

}
