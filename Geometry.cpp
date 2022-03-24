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

namespace Vx::Blaze {

    Geometry::Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                       std::vector<unsigned int> indices) :
            vertices(vertices),
            indices(indices) {
        this->indexCount = indices.size();
        this->indexOffset = 0;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);


        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Geometry::Geometry(int positionOffset, int positionLength, int normalOffset, int normalLength,
                       std::vector<unsigned char> data, int indexOffset, int indexCount) {
        printf("Loaded mesh! :)\n");

        this->indexOffset = indexOffset;
        this->indexCount = indexCount;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(unsigned char), data.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void *>(positionOffset));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void *>(normalOffset));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);

        glBindVertexArray(0);
    }


    void Geometry::Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) {
        visitor->Accept(static_pointer_cast<Geometry>(self), visitor);
    }

    void Geometry::Render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderNode> shader, glm::mat4 model) {
        if (camera) {
            glUseProgram(*shader->Shader);
            glBindVertexArray(vao);
            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(camera->Projection));
            glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(camera->View));
            glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, reinterpret_cast<const void*>(indexOffset));
            glBindVertexArray(0);
            glUseProgram(0);
        }
    }

}