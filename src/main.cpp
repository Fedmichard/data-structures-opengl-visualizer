#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <../../../header_files/shader_class.h>

void processInput(GLFWwindow* window); // Processes our input
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Resizes function 

int main() {
    // Instantiate GLFW window
    glfwInit(); // Initializes GLFW library
    // GLFW window configuration version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // which option we are configuring: GLFW_CONTEXT_VERSION_MAJOR
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // which option we are configuring: GLFW_CONTEXT_VERSION_MINOR
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Setting hint of GLFW_OPENGL_PROFILE, to the core profile

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // vertex data for shape 1
    GLfloat vertices[] = {
         0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // origin 0
         0.0f,  0.5f,  0.0f,  1.0f, 1.0f, 0.0f, // top 1
         0.5f,  0.25f, 0.0f,  1.0f, 0.0f, 1.0f, // right #1 2
         0.5f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f, // right #2 3
        -0.5f,  0.25f, 0.0f,  0.0f, 1.0f, 1.0f, // left #1 4
        -0.5f, -0.25f, 0.0f,  0.0f, 1.0f, 0.0f, // left #2 5
         0.0f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom 4 6
    };
    // index data, how we want to draw our shape based on pattern of indexes
    // 4 total indexes
    // EBO data for shape 1
    GLuint indices[] = {
        1, 2, 4, // triangle 1
        0, 2, 4, // triangle 2
        4, 0, 5, // triangle 3
        0, 5, 3, // triangle 4
        5, 3, 6, // triangle 5
    };
    // vertex data for shape 2
    GLfloat p2Vertices[] = {
        // Positions         // colors
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Left
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Right
    };
    // vertex data for shape 3
    GLfloat p3Vertices[] = {
        -0.8f, -0.8f, 0.0f, // 0 left 1
        -0.4f, -0.4f, 0.0f, // 1 top 1
        0.0f, -0.8f, 0.0f, // 2 right 1
        0.4f, -0.4f, 0.0f, // 3 top 2
        0.8f, -0.8f, 0.0f, // 4 right 2
    };
    // EBO data for shape 3
    GLint indices2[] = {
        0, 1, 2, // triangle 1
        2, 3, 4, // triangle 2
    };

    Shader Shader1("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.frag");

    // Make sure to generate the VAO before the VBO
    // Create an unsigned int titled VAO to store configurations for or object
    // Don't pass reference when you generate buffers/arrays necause we are passing an array, which is just memory
    GLuint VAO[3]; // Generate an array of 3 VAOs, VAO[0], VAO[1], VAO[2] with their own unique ids
    glGenVertexArrays(3, VAO); // Generate 3 ids for our VAO array that has 3 elements
    
    GLuint VBO[3]; // Creating a vertex buffer object so we can send our vertices and creates an id for access
    glGenBuffers(3, VBO); // Bind our VBO to the buffer type GL_ARRAY_BUFFER (VBO)

    GLuint EBO[2]; // Index buffer to store our indicies
    glGenBuffers(2, EBO); // Generate a buffer id to the reference of EBO, bind our EBO to the buffer type GL_ELEMENT_ARRAY_BUFFER

    // Object 1
    // Bind our current VAO (ALWAYS BIND VAO FIRST TO ENSURE STORING OF SUBSEQUENT OBJECTS)
    glBindVertexArray(VAO[0]);
    // Bind our current VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // bind our VBO to GL_ARRAY_BUFFER
    // VBO data for our currently binded VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // data stored in GL_ARRAY_BUFFER
    
    // create an unsigned int titled EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]); // bind GL_ELEMENT_ARRAY_BUFFER for our index buffer object EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // data stored in GL_ELEMENT_ARRAY_BUFFER

    // VBO[0] currently binded
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // how we want opengl to interpret our vertex buffer data
    glEnableVertexAttribArray(0);
    // 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Clear VBO, VAO, and EBO buffers to a null like state
    // unbind VAO first or your telling opengl to unbind VBO/EBO to unbind from the current VAO
    glBindVertexArray(0); // VAO (not really necessary)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // EBO

    // Object 2
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p2Vertices), p2Vertices, GL_STATIC_DRAW);

    // Vertex attrib. location 0; position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex attrib. location 1; color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // VAO (necessary since we have multiple)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // EBO

    // Object 3
    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p3Vertices), p3Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // VAO (necessary since we have multiple)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // EBO

    // Main while loop
    while (!glfwWindowShouldClose(window)) { 
        // PROCESSING INPUT
        processInput(window);
        // 
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;


        // RENDERING COMMANDS
        // Background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // setting the clear color
        glClear(GL_COLOR_BUFFER_BIT); // clearing our background with our clear color

        // F
        Shader1.use();
        // int vertexColorLocation3 = glGetUniformLocation(yellowShaderProgram, "ourColor");
        // activate the shader before drawing our first shape
        // glUniform4f(vertexColorLocation3, 0.0f, greenValue, 0.0f, 1.0f);
        // rebind VAO; sets the current context 
        // glBindVertexArray(VAO[1]);
        // draw elements
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // activate the shader before drawing our second shape
        // glUseProgram(shaderProgram);
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // glBindVertexArray(VAO[0]);
        // glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0); // used for our EBO

        // activate the shader before drawing our third shape
        // glUseProgram(redShaderProgram);
        // int vertexColorLocation2 = glGetUniformLocation(redShaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation2, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Check and call events and swap the buffers, to ensure image get's updated each frame
        glfwSwapBuffers(window); // swap back buffer (receives all rendering commands) and front buffer (outputs final image)
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // unbind VAO first or your telling opengl to unbind VBO/EBO to unbind from the current VAO
    glDeleteVertexArrays(3, VAO); // Delete our created vertex array to free space
    glDeleteBuffers(3, VBO); // Delete our created vertex buffer to free space
    // glDeleteProgram(shaderProgram); // delete our created shader program to free space
    // glDeleteProgram(yellowShaderProgram); // delete our created shader program to free space

    // Delete window
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}