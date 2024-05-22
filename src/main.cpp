#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <../../../header_files/shader_class.h>
#include <../../../header_files/vbo_class.h>
#include <../../../header_files/vba_class.h>
#include <../../../header_files/ebo_class.h>

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
        // Positions          // Colors
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
    GLuint indices2[] = {
        0, 1, 2, // triangle 1
        2, 3, 4, // triangle 2
    };

    Shader shader1("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.frag");
    Shader shader2("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader2.frag");
    Shader shader3("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader3.frag");

    // Object 1
    VBA VBA1;
    VBA1.bind();
    // Bind our current VBO
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex attrib. location 1; color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // VBO[0] currently binded
    // Clear VBO, VAO, and EBO buffers to a null like state
    // unbind VAO first or your telling opengl to unbind VBO/EBO to unbind from the current VAO
    VBA1.unBind(); // VAO (not really necessary)
    VBO1.unBind();
    EBO1.unBind();

    // Object 2
    VBA VBA2;
    VBA2.bind();
    VBO VBO2(p2Vertices, sizeof(p2Vertices));

    // Vertex attrib. location 0; position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex attrib. location 1; color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VBA2.unBind(); // VAO (necessary since we have multiple)
    VBO2.unBind(); // VBO

    // Object 3
    VBA VBA3;
    VBA3.bind();
    VBO VBO3(p3Vertices, sizeof(p3Vertices));
    EBO EBO2(indices2, sizeof(indices2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    VBA3.unBind(); // VAO (not really necessary)
    VBO3.unBind();
    EBO2.unBind();

    // Main while loop
    while (!glfwWindowShouldClose(window)) { 
        // PROCESSING INPUT
        processInput(window);
        // 
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float moveValue = (cos(timeValue) * sin(timeValue));


        // RENDERING COMMANDS
        // Render background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // setting the clear color
        glClear(GL_COLOR_BUFFER_BIT); // clearing our background with our clear color

        // Render shapes
        shader2.use();
        shader2.setFloat("offset", moveValue);
        VBA2.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shader1.use();
        VBA1.bind();
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        shader3.use();
        shader2.setFloat("offset", moveValue);
        shader3.setFloat4("ourColor", 0.0f, greenValue, 0.0f);
        VBA3.bind();
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers, to ensure image get's updated each frame
        glfwSwapBuffers(window); // swap back buffer (receives all rendering commands) and front buffer (outputs final image)
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // unbind VAO first or your telling opengl to unbind VBO/EBO to unbind from the current VAO
    // Delete our created vertex buffer to free space
    VBA1.remove();
    VBA2.remove();
    VBA3.remove();
    VBO1.remove();
    VBO2.remove();
    VBO3.remove();
    EBO1.remove();
    EBO2.remove();

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