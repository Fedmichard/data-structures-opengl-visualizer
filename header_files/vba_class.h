#ifndef VBA_H
#define VBA_H

#include <GLAD/glad.h>
#include <../../../header_files/vbo_class.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VBA
{
public:
    GLuint ID;
    VBA();
    void bind();
    void unBind();
    void remove();
};

#endif