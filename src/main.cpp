#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader Source
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader Source
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {
    // Instantiate GLFW window
    glfwInit(); // Initializes GLFW library
    // GLFW window configuration version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // which option we are configuring: GLFW_CONTEXT_VERSION_MAJOR
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // which option we are configuring: GLFW_CONTEXT_VERSION_MINOR
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates our window 800 x 800 titled hello world
    GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World!", NULL, NULL);
    // If window fails to create
    if (window == NULL) {
        std::cout << "Failed to created GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Introduce window into the current context
    glfwMakeContextCurrent(window);
    // Load GLAD so it configures to OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the window
    glViewport(0, 0, 800, 800);

    // vertex data
    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // create a new vertex shader to draw the points
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Make sure to generate the VAO before the VBO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Main while loop
    while (!glfwWindowShouldClose(window)) { 
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Delete window
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}