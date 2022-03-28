//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_GEOMETRY_H
#define VXBLAZE_GEOMETRY_H

#include <vector>
#include <GL/glew.h>

#include "Node.h"
#include "glm/glm.hpp"
#include "Material.h"
#include <map>

namespace Vx::Blaze {

    class Camera;

    class ResourceManager;

    class ShaderNode;

    template<typename T>
    class Buffer;

    class Accessor;

    class Shader;

    class EnvironmentNode;

    class Geometry : public Node {

        std::shared_ptr<Material> material;
        std::vector<glm::vec3> vertices;
        int indexCount;
        int indexOffset;
        std::shared_ptr<Buffer<void>> vbo;
        std::map<std::shared_ptr<Shader>, GLuint> vaos;
        std::map<std::string, std::shared_ptr<Accessor>> attributes;
        std::shared_ptr<Accessor> indices;

        GLuint vao;
        GLuint ibo;
        GLuint nbo;

    public:
        Geometry(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);

        Geometry(std::map<std::string, std::shared_ptr<Accessor>> attributes, std::shared_ptr<Accessor> indices,
                 std::shared_ptr<Material> material = nullptr);

        void Visit(std::shared_ptr<NodeVisitor> visitor, std::shared_ptr<Node> self) override;

        void Render(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader, glm::mat4 model,
                    std::shared_ptr<EnvironmentNode> env = nullptr);
    };

}

#endif //VXBLAZE_GEOMETRY_H
