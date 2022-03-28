//
// Created by voxed on 3/25/22.
//

#ifndef VXBLAZE_BUFFER_H
#define VXBLAZE_BUFFER_H

#include <GL/glew.h>
#include <vector>

namespace Vx::Blaze {
    template <>
    class Buffer<void> {
    public:
        virtual void Bind(GLenum target) = 0;
    };

    template <typename T>
    class Buffer : public Buffer<void> {
        GLuint bufferId;

    public:
        explicit Buffer(std::vector<T> data) {
            glGenBuffers(1, &bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void Bind(GLenum target) override {
            glBindBuffer(target, bufferId);
        }
    };

}

#endif //VXBLAZE_BUFFER_H
