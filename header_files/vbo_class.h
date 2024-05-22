#ifndef VBO_H
#define VBO_H

#include <GLAD/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VBO {
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLuint size);

    void bind();
    void unBind();
    void remove();
};

#endif