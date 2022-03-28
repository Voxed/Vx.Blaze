//
// Created by voxed on 3/28/22.
//

#include "FrameBuffer.h"

#include "Texture.h"

namespace Vx::Blaze {

    FrameBuffer::FrameBuffer() : Color(std::make_shared<Texture>()){
        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Color->Id, 0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
    }

    void FrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

}
