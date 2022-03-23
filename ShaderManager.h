//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_SHADERMANAGER_H
#define VXBLAZE_SHADERMANAGER_H


#include <string>
#include <map>
#include <GL/glew.h>
#include <memory>

namespace Vx::Blaze {

    struct ShaderDeleter {
        void operator()(GLuint * p) {
            glDeleteProgram(*p);
            delete p;
        }
    };

    class ShaderManager {
        std::map<std::string, std::weak_ptr<GLuint>> programs;

    public:
        std::shared_ptr<GLuint> Get(std::string name);
    };

}

#endif //VXBLAZE_SHADERMANAGER_H
