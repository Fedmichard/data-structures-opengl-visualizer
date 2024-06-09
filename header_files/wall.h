#ifndef WALL_H
#define WALL_H

#include <GLAD/glad.h>
#include <../../../header_files/ant.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>
#include <../../../header_files/shader_class.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Wall {
private:
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    void setAABB();

public:
    AABB wall;
    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec3 Position;
    glm::vec3 Size;
    
    Wall(Shader& shader, glm::vec3 pos, glm::vec3 size, GLfloat Angle);
    ~Wall();

    bool checkCollision( Ant& ant );


};

#endif