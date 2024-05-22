#ifndef EBO_H
#define EBO_H

#include <GLAD/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class EBO {
public:
    GLuint ID;
    EBO(GLuint* indices, GLuint count);

    void bind();
    void unBind();
    void remove();
};

#endif