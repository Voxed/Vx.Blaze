//
// Created by voxed on 3/28/22.
//

#ifndef VXBLAZE_TEXTURE_H
#define VXBLAZE_TEXTURE_H

#include <vector>
#include <GL/glew.h>

namespace Vx::Blaze {

    class Texture {
    public:
        GLuint Id;
        int Height = 0;
        int Width = 0;

        Texture(std::vector<unsigned char> data, int width, int height, GLint internalFormat, GLenum format);
        Texture(std::vector<float> data, int width, int height, GLint internalFormat, GLenum format);
        Texture();

        void Bind(GLenum slot);
    };

}

#endif //VXBLAZE_TEXTURE_H
