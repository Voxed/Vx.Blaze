//
// Created by voxed on 3/23/22.
//

#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

namespace Vx::Blaze {

    Shader::Shader(GLuint program) : program(program) {

    }

    GLint Shader::GetAttributeLocation(std::string name) {
        if(!attributes.contains(name)) {
            attributes[name] = glGetAttribLocation(program, name.c_str());
            if (attributes[name] == -1) {
                printf("ATTRIBUTE NOT FOUND: %s\n", name.c_str());
            }
        }
        return attributes[name];
    }

    void Shader::Use() const {
        glUseProgram(program);
    }

    void Shader::Delete() const {
        glDeleteProgram(program);
    }

    GLint Shader::GetUniformLocation(std::string name) {
        if(!uniforms.contains(name)) {
            uniforms[name] = glGetUniformLocation(program, name.c_str());
            if (uniforms[name] == -1) {
                printf("UNIFORM NOT FOUND: %s\n", name.c_str());
            }
        }
        return uniforms[name];
    }

    void Shader::SetUniform(std::string name, glm::mat4 value) {
        Use();
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
        glUseProgram(0);
    }

    void Shader::SetUniform(std::string name, glm::vec3 value) {
        Use();
        glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
        glUseProgram(0);
    }

    void Shader::SetUniform(std::string name, float value) {
        Use();
        glUniform1f(GetUniformLocation(name), value);
        glUseProgram(0);
    }

}
