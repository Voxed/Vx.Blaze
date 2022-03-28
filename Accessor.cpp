//
// Created by voxed on 3/25/22.
//

#include "Accessor.h"
#include "BufferView.h"

namespace Vx::Blaze {

    Accessor::Accessor(std::shared_ptr<Vx::Blaze::BufferView> bufferView, GLsizei componentCount,
                       GLenum componentType, GLsizei count) :
            BufferView(bufferView), ComponentCount(componentCount), ComponentType(componentType), Count(count) {
    }

}
