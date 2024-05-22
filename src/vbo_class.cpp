#include <../../../header_files/vbo_class.h>

VBO::VBO(GLfloat* vertices, GLuint size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID); // bind our VBO to GL_ARRAY_BUFFER
    // VBO data for our currently binded VBO
    // 2nd param could have a GLsizeiptr size variable instead
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // data stored in GL_ARRAY_BUFFER
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID); // bind our VBO to GL_ARRAY_BUFFER
}

void VBO::unBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove() {
    glDeleteBuffers(1, &ID);
}