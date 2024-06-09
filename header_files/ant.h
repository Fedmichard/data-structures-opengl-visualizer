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
private:
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    void setAABB();
    

public:
    AABB box;
    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec3 Position;
    glm::vec3 Size;

    Ant(Shader& shader, glm::vec3 position, glm::vec3 size, GLfloat angle);
    ~Ant();

    bool testAABB(Ant::AABB& other);
};

#endif