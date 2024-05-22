#ifndef SHADERS_H
#define SHADERS_H

#include <GLAD/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
private:
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type);
};


#endif