#include <../../../header_files/vao_class.h>

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unBind() {
    glBindVertexArray(0);
}

void VAO::remove() {
    glDeleteVertexArrays(1, &ID);
}