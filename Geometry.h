//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_GEOMETRY_H
#define VXBLAZE_GEOMETRY_H

#include <vector>
#include <GL/glew.h>

#include "Node.h"
#include "glm/glm.hpp"

namespace Vx::Blaze {

    class Camera;
    class ResourceManager;
    class ShaderNode;

    class Geometry : public Node {
        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;

        GLuint vao;
        GLuint ibo;
        GLuint vbo;
        GLuint nbo;

    public:
        Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;

        void Render(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderNode> shader, glm::mat4 model);
    };

}

#endif //VXBLAZE_GEOMETRY_H
