//
// Created by voxed on 3/28/22.
//

#include "Texture.h"

namespace Vx::Blaze {

    Texture::Texture(std::vector<unsigned char> data, int width, int height, GLint internalFormat, GLenum format) {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        Height = height;
        Width = width;
    }

    void Texture::Bind(GLenum slot) {
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, Id);
    }

    Texture::Texture(std::vector<float> data, int width, int height, GLint internalFormat, GLenum format) {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
                     GL_FLOAT, data.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        Height = height;
        Width = width;
    }

    Texture::Texture() {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}
