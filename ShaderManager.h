//
// Created by voxed on 3/23/22.
//

#ifndef VXBLAZE_SHADERMANAGER_H
#define VXBLAZE_SHADERMANAGER_H


#include <string>
#include <map>
#include <GL/glew.h>
#include <memory>
#include "Shader.h"

namespace Vx::Blaze {

    struct ShaderDeleter {
        void operator()(Shader * p) {
            p->Delete();
            delete p;
        }
    };

    class ShaderManager {
        std::map<std::string, std::weak_ptr<Shader>> programs;

    public:
        std::shared_ptr<Shader> Get(std::string name);
    };

}

#endif //VXBLAZE_SHADERMANAGER_H
