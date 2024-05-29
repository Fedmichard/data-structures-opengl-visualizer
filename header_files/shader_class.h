#ifndef SHADERS_H
#define SHADERS_H

#include <GLAD/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>

class Shader {
public:
    // The program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use or activate the shader program
    void use();
    // delete the shader program
    void remove();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setFloat4(const std::string &name, float r, float g, float b) const;
    void setMat4(const std::string &name, glm::mat4 trans) const; 
private:
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type);
};


#endif