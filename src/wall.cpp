#include <../../../header_files/wall.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>
#include <iostream>

void Wall::setAABB() {

    wall.min = Position + (-(glm::vec3(0.035f, 1.0f, 0.0f)));
    wall.max = Position + (glm::vec3(0.125f, 1.0f, 0.0f));

}

Wall::Wall(Shader& shader, glm::vec3 pos, glm::vec3 size, GLfloat Angle) {
    Position = pos;
    Size = size;

    Model = glm::translate(Model, Position);
    Model = glm::rotate(Model ,Angle, glm::vec3(0.0f, 0.0f, 1.0f));
    Model = glm::scale(Model, Size);

    setAABB();

    shader.setMat4("model", Model);
    glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
}

bool Wall::checkCollision(Ant& ant) {
    float d1x = wall.min.x - ant.box.max.x;
    float d1y = wall.min.y - ant.box.max.y;
    float d2x = ant.box.max.x - wall.max.x;
    float d2y = ant.box.max.y - wall.max.y;

    // if the value is not negative, no collision
    if (d1x > 0.0f || d1y > 0.0f) {
        return false;
    }

    if (d2x > 0.0f || d2y > 0.0f) {
        return false;
    }

    return true;
}

Wall::~Wall() {

}