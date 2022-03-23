//
// Created by voxed on 3/23/22.
//

#include <fstream>
#include <vector>
#include "ShaderManager.h"

namespace Vx::Blaze {

    std::shared_ptr<GLuint> ShaderManager::Get(std::string path) {
        if(programs.contains(path)) {
            if(std::shared_ptr<GLuint> shared = programs[path].lock())
                return shared;
        }

        std::ifstream fragmentSourceStream(path + ".frag");
        std::ifstream vertexSourceStream(path + ".vert");
        std::string fragmentSource((std::istreambuf_iterator<char>(fragmentSourceStream)),
                        std::istreambuf_iterator<char>());
        std::string vertexSource((std::istreambuf_iterator<char>(vertexSourceStream)),
                        std::istreambuf_iterator<char>());

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char* fragmentSourceCString = fragmentSource.c_str();
        const char* vertexSourceCString = vertexSource.c_str();

        glShaderSource(vertexShader, 1, &vertexSourceCString, NULL);
        glShaderSource(fragmentShader, 1, &fragmentSourceCString, NULL);

        glCompileShader(vertexShader);
        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

            printf("Oops: %s\n", errorLog.data());
        }

        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

            printf("Oops: %s\n", errorLog.data());
        }

        GLuint program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            printf("Oops: %s\n", infoLog.data());

        }

        auto shared = std::shared_ptr<GLuint>(new GLuint(program), ShaderDeleter());
        programs[path] = shared;
        return shared;
    }

}
