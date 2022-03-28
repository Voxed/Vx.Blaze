//
// Created by voxed on 3/25/22.
//

#include "BufferView.h"

namespace Vx::Blaze {

    BufferView::BufferView(std::shared_ptr<Vx::Blaze::Buffer<void>> buffer, GLsizei length, GLsizei stride,
                           const void *offset) :
            Buffer(buffer), Length(length), Stride(stride), Offset(offset) {
    }

}
