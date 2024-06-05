#include <../../../header_files/ant.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>
#include <iostream>

void Ant::setAABB() {

    box.min = Position + (-Size);
    box.max = Position + Size;

}

Ant::Ant(Shader& shader, glm::vec3 position, glm::vec3 size, GLfloat angle) {
    Position = position;
    Size = size;

    Model = glm::translate(Model, Position);
    Model = glm::rotate(Model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    Model = glm::scale(Model, Size);

    setAABB();

    shader.setMat4("model", Model);
    glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
}

bool Ant::testAABB(AABB& other) {
    float d1x = box.min.x - other.max.x;
    float d1y = box.min.y - other.max.y;
    float d2x = other.min.x - box.max.x;
    float d2y = other.min.y - box.max.y;

    // if the value is not negative, no collision
    if (d1x > 0.0f || d1y > 0.0f) {
        return false;
    }

    if (d2x > 0.0f || d2y > 0.0f) {
        return false;
    }

    return true;
}

Ant::~Ant() {

}

