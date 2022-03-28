//
// Created by voxed on 3/25/22.
//

#ifndef VXBLAZE_ACCESSOR_H
#define VXBLAZE_ACCESSOR_H


#include <GL/glew.h>
#include <memory>

namespace Vx::Blaze {

    class BufferView;

    class Accessor {
    public:
        const std::shared_ptr<Vx::Blaze::BufferView> BufferView;
        const GLsizei ComponentCount;
        const GLsizei Count;
        const GLenum ComponentType;

        Accessor(std::shared_ptr<Vx::Blaze::BufferView> bufferView, GLsizei componentCount, GLenum componentType,
                 GLsizei count);
    };

}

#endif //VXBLAZE_ACCESSOR_H
