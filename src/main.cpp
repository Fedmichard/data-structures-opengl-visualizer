#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <../../../header_files/shader_class.h>
#include <../../../header_files/vbo_class.h>
#include <../../../header_files/vao_class.h>
#include <../../../header_files/ebo_class.h>
#include <../../../header_files/two_d_texture_class.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../../header_files/stb_image.h"

void processInput(GLFWwindow* window); // Processes our input
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Resizes function 

GLfloat opacity = 0.2f;
GLfloat offsetX = 0.0f;
GLfloat offsetY = 0.0f;

int main() {
    // Instantiate GLFW window
    glfwInit(); // Initializes GLFW library
    // GLFW window configuration version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // which option we are configuring: GLFW_CONTEXT_VERSION_MAJOR
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // which option we are configuring: GLFW_CONTEXT_VERSION_MINOR
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Setting hint of GLFW_OPENGL_PROFILE, to the core profile
    stbi_set_flip_vertically_on_load(true); // images will load right side up

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
        // Positions          // Colors          // Texture coords
         0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // origin 0
         0.0f,  0.5f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 2.0f, // top 1
         0.5f,  0.25f, 0.0f,  1.0f, 0.0f, 1.0f,  2.0f, 1.5f, // right #1 2
         0.5f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f,  2.0f, 0.5f, // right #2 3
        -0.5f,  0.25f, 0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.5f, // left #1 4
        -0.5f, -0.25f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.5f, // left #2 5
         0.0f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom 4 6
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

    Shader shader1("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.frag");
    Shader shader2("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader2.frag");
    Shader shader3("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader3.frag");

    // Generate texture ID and store it within our texture instances ID variable 
    // texture0
    glActiveTexture(GL_TEXTURE0);
    TwoDTexture texture0;

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture0.genTexture("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Textures/container.jpg");

    glActiveTexture(GL_TEXTURE1);
    TwoDTexture texture1;

    // set the texture wrapping/filtering options (on the currently bound texture object)
    // set the parameters for the x axis to repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // set the parameters for the y axis to repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set the parameters for when minimizing to a linear mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // set the parameters for when magnifying to linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture1.genTexture("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Textures/maxresdefault.jpg");

    // Object 1
    VAO VAO1;
    // Bind our current VBO
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex attrib. location 1; color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // vertrex attrib. location 2; texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    VAO1.unBind(); // VAO (not really necessary)
    VBO1.unBind();
    EBO1.unBind();

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
        // shader2.use();
        // shader2.setFloat("offset", moveValue);
        // VAO2.bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        shader1.use();
        // Automatically when we bind our first texture, texture unit 0 binds to that and activates
        shader1.setFloat("opacity", opacity);
        shader1.setFloat("offsetX", offsetX);
        shader1.setFloat("offsetY", offsetY);
        shader1.setInt("texture1", 0);
        // or set it via the texture class
        shader1.setInt("texture2", 1);
        // shader3.setFloat4("ourColor", greenValue, greenValue - 0.1f, moveValue - 0.2f);
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers, to ensure image get's updated each frame
        glfwSwapBuffers(window); // swap back buffer (receives all rendering commands) and front buffer (outputs final image)
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // unbind VAO first or your telling opengl to unbind VBO/EBO to unbind from the current VAO
    // Delete our created vertex buffer to free space
    VAO1.remove();
    VBO1.remove();
    EBO1.remove();

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
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        opacity += 0.0001f;

        if (opacity >= 1.0f) {
            opacity = 1.0f;
        }

    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        opacity -= 0.0001f;

        if (opacity <= 0.0f) {
            opacity = 0.0f;
        }

    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        offsetX -= 0.001f;
        std::cout << "Offset on x: " << offsetX << std::endl;

        if (offsetX <= -1.0f) {
            offsetX = -1.0f;
        }

    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        offsetX += 0.001f;
        std::cout << "Offset on x: " << offsetX << std::endl;

        if (offsetX >= 1.0f) {
            offsetX = 1.0f;
        }

    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        offsetY += 0.001f;
        std::cout << "Offset on x: " << offsetY << std::endl;

        if (offsetY >= 1.0f) {
            offsetY = 1.0f;
        }

    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        offsetY -= 0.001f;
        std::cout << "Offset on x: " << offsetY << std::endl;

        if (offsetY <= -1.0f) {
            offsetY = -1.0f;
        }

    }
}