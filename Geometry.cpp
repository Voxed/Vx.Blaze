//
// Created by voxed on 3/23/22.
//

#include "Geometry.h"

#include <utility>
#include <glm/gtc/type_ptr.hpp>
#include "NodeVisitor.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "ShaderNode.h"
#include "Buffer.h"
#include "Accessor.h"
#include "BufferView.h"
#include "EnvironmentNode.h"
#include "Texture.h"

namespace Vx::Blaze {

    void Geometry::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<Geometry>(self), visitor);
    }

    void Geometry::Render(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader, glm::mat4 model,
                          std::shared_ptr<EnvironmentNode> env) {
        if (!vaos.contains(shader)) {
            // Initialize vao
            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            for (const auto &item: attributes) {
                GLint location = shader->GetAttributeLocation(item.first);
                std::shared_ptr<Accessor> accessor = item.second;

                accessor->BufferView->Buffer->Bind(GL_ARRAY_BUFFER);
                if (location != -1) {
                    printf("%i %s %i %i %i %i\n", location, item.first.c_str(), accessor->ComponentCount,
                           accessor->ComponentType, accessor->BufferView->Stride, accessor->BufferView->Offset);
                    glVertexAttribPointer(location, accessor->ComponentCount, accessor->ComponentType, GL_FALSE,
                                          accessor->BufferView->Stride, accessor->BufferView->Offset);
                    glEnableVertexAttribArray(location);
                }
            }

            indices->BufferView->Buffer->Bind(GL_ELEMENT_ARRAY_BUFFER);

            glBindVertexArray(0);

            vaos[shader] = vao;
        }
        glBindVertexArray(vaos[shader]);
        if (camera) {
            shader->SetUniform("PROJECTION", camera->Projection);
            shader->SetUniform("VIEW", camera->View);
        }
        shader->SetUniform("MODEL", model);
        if (material) {
            shader->SetUniform("COLOR", material->Color);
            shader->SetUniform("ROUGHNESS", material->Roughness);
            shader->SetUniform("METALNESS", material->Metallic);
        }
        if(env) {
            env->Texture->Bind(GL_TEXTURE6);
            shader->SetUniform("ENVIRONMENT", GL_TEXTURE6);
        }

        shader->Use();
        glDrawElements(GL_TRIANGLES, indices->Count, indices->ComponentType,
                       reinterpret_cast<const void *>(indices->BufferView->Offset));
        glUseProgram(0);
        glBindVertexArray(0);
    }

    Geometry::Geometry(std::map<std::string, std::shared_ptr<Accessor>> attributes, std::shared_ptr<Accessor> indices,
                       std::shared_ptr<Material> material)
            : attributes(
            std::move(attributes)), indices(indices), material(material) {}

    Geometry::Geometry(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) {
        this->indices = std::make_shared<Vx::Blaze::Accessor>(
                std::make_shared<Vx::Blaze::BufferView>(
                        std::make_shared<Vx::Blaze::Buffer<unsigned int>>(
                                indices
                        ), 6, 0, (void *) 0),
                1, GL_UNSIGNED_INT, 6);

        auto dataAccessor = std::make_shared<Vx::Blaze::Accessor>(std::make_shared<Vx::Blaze::BufferView>(
                std::make_shared<Vx::Blaze::Buffer<glm::vec3>>(
                        vertices
                ), 6, 0, (void *) 0), 3, GL_FLOAT, 4);

        attributes = std::map<std::string, std::shared_ptr<Vx::Blaze::Accessor>>{
                {"POSITION", dataAccessor}
        };
    }

}