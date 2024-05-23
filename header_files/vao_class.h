#ifndef VAO_H
#define VAO_H

#include <GLAD/glad.h>
#include <../../../header_files/vbo_class.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VAO
{
public:
    GLuint ID;
    VAO();
    void bind();
    void unBind();
    void remove();
};

#endif