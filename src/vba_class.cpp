#include <../../../header_files/vba_class.h>

VBA::VBA() {
    glGenVertexArrays(1, &ID);
}

void VBA::bind() {
    glBindVertexArray(ID);
}

void VBA::unBind() {
    glBindVertexArray(0);
}

void VBA::remove() {
    glDeleteVertexArrays(1, &ID);
}