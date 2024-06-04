#ifndef ANT_H
#define ANT_H

#include <GLAD/glad.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>
#include <../../../header_files/shader_class.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Ant {
public:
    bool Collision;
    glm::mat4 Model = glm::mat4(1.0f);

    Ant(Shader& shader, glm::vec3 Position, glm::vec3 Size, float Angle);
    ~Ant();
    
private:
    // Collision box of each ant
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    bool testAABB(AABB* a, AABB* b) {
        // if this is negative they have collided
        float d1x = b->min.x - a->max.x;
        float d1y = b->min.y - a->max.y;
        float d2x = a->min.x - b->max.x;
        float d2y = a->min.y - b->max.y;

        // if the value is not negative, no collision
        if (d1x > 0.0f || d1y > 0.0f) {
            Collision = false;
        }

        if (d2x > 0.0f || d2y > 0.0f) {
            Collision = false;
        }

        Collision = true;
    }

};

#endif