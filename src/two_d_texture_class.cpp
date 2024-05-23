#include <iostream>

#include "../../../header_files/two_d_texture_class.h"
#include "../../../header_files/stb_image.h"

TwoDTexture::TwoDTexture() {     
    // Generate texture ID and store it within our texture instances ID variable     
    glGenTextures(1, &ID);
    // bind our texture ID to opengl 2d texture object
    glBindTexture(GL_TEXTURE_2D, ID);
    // load and generate our texture
    
}

void TwoDTexture::genTexture(char* texture) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture,
                                    &width, &height, &nrChannels, 0);
    // Error checking
    if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        // free image from memory
        stbi_image_free(data);
}

void TwoDTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void TwoDTexture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TwoDTexture::remove() {
    glDeleteTextures(GL_TEXTURE_2D, &ID);
}