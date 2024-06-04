#include <../../../header_files/ant.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>

Ant::Ant(Shader& shader, glm::vec3 Position, glm::vec3 Size, float Angle) {

    Model = glm::translate(Model, Position);
    Model = glm::rotate(Model, Angle, glm::vec3(0.0f, 0.0f, 1.0f));
    Model = glm::scale(Model, Size);

    shader.setMat4("model", Model);
    glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
}

Ant::~Ant() {

}