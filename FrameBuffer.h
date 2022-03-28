//
// Created by voxed on 3/28/22.
//

#ifndef VXBLAZE_FRAMEBUFFER_H
#define VXBLAZE_FRAMEBUFFER_H


#include <memory>
#include <GL/glew.h>

namespace Vx::Blaze {

    class Texture;

    class FrameBuffer {
        GLuint id;

    public:
        const std::shared_ptr<Texture> Color;

        FrameBuffer();

        void Bind();
    };

}


#endif //VXBLAZE_FRAMEBUFFER_H
