//
// Created by voxed on 3/25/22.
//

#ifndef VXBLAZE_BUFFERVIEW_H
#define VXBLAZE_BUFFERVIEW_H

#include <memory>
#include <GL/glew.h>

namespace Vx::Blaze {

    template <typename T>
    class Buffer;

    class BufferView {
    public:
        const std::shared_ptr<Vx::Blaze::Buffer<void>> Buffer;
        const GLsizei Length;
        const void* Offset;
        const GLsizei Stride;

        BufferView(std::shared_ptr<Vx::Blaze::Buffer<void>> buffer, GLsizei length, GLsizei stride, const void* offset);
    };

}

#endif //VXBLAZE_BUFFERVIEW_H
