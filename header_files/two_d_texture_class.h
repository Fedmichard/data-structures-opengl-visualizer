#ifndef TWO_D_TEXTURES_H
#define TWO_D_TEXTURES_H

#include <GLAD/glad.h>

class TwoDTexture {
public:
    GLuint ID;
    TwoDTexture();
    void genTexture(char* texture);
    void bind();
    void unbind();
    void remove();
};

#endif