#include <../../../header_files/collision.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>

AABB::AABB(glm::vec3 position, glm::vec3 size) {
    min = position + (-size);
    max = position + size;
}

AABB::~AABB() {

}