//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_SHADER_H
#define VXBLAZE_SHADER_H

#include <GL/glew.h>
#include <map>
#include <string>
#include <glm/glm.hpp>

namespace Vx::Blaze {

    class Shader {
        GLuint program;
        std::map<std::string, GLint> attributes;
        std::map<std::string, GLint> uniforms;

    public:
        explicit Shader(GLuint program);

        GLint GetAttributeLocation(std::string);
        GLint GetUniformLocation(std::string);

        void SetUniform(std::string name, glm::mat4 value);
        void SetUniform(std::string name, float value);

        void Use() const;

        void Delete() const;

        void SetUniform(std::string name, glm::vec3 value);
    };

}

#endif //VXBLAZE_SHADER_H
