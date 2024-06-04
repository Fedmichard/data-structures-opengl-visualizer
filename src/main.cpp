#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <../../../header_files/shader_class.h>
#include <../../../header_files/vbo_class.h>
#include <../../../header_files/vao_class.h>
#include <../../../header_files/ebo_class.h>
#include <../../../header_files/two_d_texture_class.h>
#include <../../../header_files/ant.h>
#define STB_IMAGE_IMPLEMENTATION
#include <../../../header_files/stb_image.h>
#include <../../../header_files/glm/glm.hpp>
#include <../../../header_files/glm/gtc/matrix_transform.hpp>
#include <../../../header_files/glm/gtc/type_ptr.hpp>

GLfloat opacity = 0.2f;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;
GLfloat offsetX = 0.0f;
GLfloat offsetY = 0.0f;
GLfloat angle;
glm::vec3 direction;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

void processInput(GLFWwindow* window, glm::vec3 direction); // Processes our input
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Resizes function 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool testAABB(AABB* a, AABB* b);

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
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);
 

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

    GLfloat vertices2[] = {
        // Vertices          // Texture   
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        // Vertices          // Texture
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        // Vertices          // Texture
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        // Vertices          // Texture
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        // Vertices          // Texture
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        // Vertices          // Texture
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Walls
    GLfloat vertices3[] = {
        // Vertices          // Texture   
        -1.0f, 1.0f, 0.0f, // Top left 1      - 0
        -0.975f, 0.975f, 0.0f, // Top Left 2      - 1
        -1.0f, 0.975f, 0.0f, //                 - 2
        -1.0f, -1.0f, 0.0f, // Bottom Left 1  - 3
        -0.975f, -0.975f, 0.0f, // Bottom Left 2  - 4
        -1.0f, -0.975f, 0.0f, //                - 5
        1.0f,  1.0f, 0.0f, // Top Right 1     - 6
        0.975f, 0.975f, 0.0f, // Top Right 2      - 7
        1.0f, 0.975f, 0.0f, //                  - 8
        1.0f,  -1.0f, 0.0f, // Bottom Right 1 - 9
        0.975f, -0.975f, 0.0f, // Bottom Right 2  - 10
        1.0f, -0.975f, 0.0f, //                 - 11
    };

    GLuint indices3[] = {
        // Top Rectangle
        0, 6, 2,
        2, 6, 8,

        // Left Rectangle
        2, 1, 5,
        1, 4, 5,

        // Bottom Rectangle
        3, 9, 5,
        9, 11, 5,

        // Right Rectangle
        7, 8, 10,
        8, 11, 10,
    };

    // Ants
    GLfloat vertices4[] = {
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };

    GLuint indices4[] = {
        0, 1, 2,
        1, 2, 3,
    };

    Shader shader1("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.frag");
    Shader shader2("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader2.frag");
    Shader shader3("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader3.frag");
    Shader shader4("C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/shader.vert",
                   "C:/Users/franc/OneDrive - Florida Gulf Coast University/Documents/1_Projects/visual/resource_files/Shaders/antShader.frag");

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

    VAO VAO2;
    VBO VBO2(vertices2, sizeof(vertices2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    VAO2.unBind(); // VAO (not really necessary)
    VBO2.unBind();

    VAO VAO3;
    VBO VBO3(vertices3, sizeof(vertices3));
    EBO EBO3(indices3, sizeof(indices3));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    VAO3.unBind();
    VBO3.unBind();
    EBO3.unBind();

    VAO VAOBug;
    VBO VBO4(vertices4, sizeof(vertices4));
    EBO EBO4(indices4, sizeof(indices4));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    VAOBug.unBind();
    VBO4.unBind();
    EBO4.unBind();
    

    // Main while loop
    while (!glfwWindowShouldClose(window)) { 
        // Processing ant movement in direction
        angle = glm::radians(rotationZ * 90.0f);
        glm::vec3 direction = glm::normalize(glm::vec3(-sin(angle), cos(angle), 0.0f));

        // PROCESSING INPUT
        processInput(window, direction);

        // Processing time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Movement
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float moveValue = (cos(timeValue) * sin(timeValue));


        // RENDERING COMMANDS
        // Render background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // setting the clear color
        glClear(GL_COLOR_BUFFER_BIT); // clearing our background with our clear color

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind our shader and our vertex array buffer
        shader3.use();
        VAO3.bind();
        // Automatically when we bind our first texture, texture unit 0 binds to that and activates
        // shader1.setFloat("opacity", opacity);
        // set our first texture
        // shader1.setInt("texture1", 0);
        // or set it via the texture class
        // shader1.setInt("texture2", 1);
        
        // set our transformation object 1
        // glm::mat4 projection = glm::perspective(glm::radians(90.0f), 800.0f/600.0f, 0.1f, 100.0f);
        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1000.0f, 1000.0f);
        // Camera setup
        glm::mat4 view = glm::mat4(1.0f);
        // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // cube setup
        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, glm::radians(rotationX * 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        // model = glm::scale(model, glm::vec3(0.0125f, 0.025f, 0.0f));

        shader3.setMat4("projection", projection);
        shader3.setMat4("view", view);
        shader3.setMat4("model", model);

        // Binding box

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);

        shader4.use();
        VAOBug.bind();

        glm::vec3 position = glm::vec3(offsetX, offsetY, 0.0f);
        glm::vec3 size = glm::vec3(0.05, 0.1, 0.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, size);

        // Binding box
        AABB ant1;
        ant1.min = position + (-size);
        ant1.max = position + size;

        shader4.setMat4("projection", projection);
        shader4.setMat4("view", view);
        shader4.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);

        shader4.setMat4("projection", projection);
        shader4.setMat4("view", view);

        Ant ant3(shader4, glm::vec3(-0.25f, 0.0f, 0.0f), glm::vec3(0.05, 0.1, 0.0f), 0.0f);
        Ant ant4(shader4, glm::vec3(-0.45f, 0.0f, 0.0f), glm::vec3(0.05, 0.1, 0.0f), 0.0f);
        Ant ant5(shader4, glm::vec3(-0.85f, 0.0f, 0.0f), glm::vec3(0.05, 0.1, 0.0f), 0.0f);

        for (GLuint i = 1; i < 2; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::vec3 position1 = glm::vec3(0.0f + i * 0.15f, 0.0f, 0.0f);
            glm::vec3 size = glm::vec3(0.05, 0.1, 0.0f);
            model = glm::translate(model, position1);
            // model = glm::rotate(model, glm::radians(0.0f + (i * 36.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, size);

            // binding box
            AABB ant2;
            ant2.min = position1 + (-size);
            ant2.max = position1 + size;
            std::cout << testAABB(&ant1, &ant2) << std::endl;
            if (testAABB(&ant1, &ant2)) {
                position = position - glm::vec3(0.1f, 0.1f, 0.0f);
            }

             shader4.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
        }

        // Box 2.1
        // model = glm::rotate(model, glm::radians(moveValue * 1.5f * 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // model = glm::rotate(model, glm::radians(-moveValue * 0.5f  * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::translate(model, glm::vec3(2.3f, 0.0f, 2.5f));

        // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        // shader1.setMat4("model", model);
        // shader3.setFloat4("ourColor", greenValue, greenValue - 0.1f, moveValue - 0.2f);
        // glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // Box 2
        // model = glm::rotate(model, glm::radians(moveValue * 2.25f * 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // model = glm::rotate(model, glm::radians(-moveValue * 1.25f * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::translate(model, glm::vec3(-3.8f, -2.0f, 1.3));

        // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        // shader1.setMat4("model", model);
        // shader3.setFloat4("ourColor", greenValue, greenValue - 0.1f, moveValue - 0.2f);
        // glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // Box 3
        // model = glm::rotate(model, glm::radians(moveValue * 3.75f * 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // model = glm::rotate(model, glm::radians(-moveValue * -2.75f * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::translate(model, glm::vec3(-1.3f, 1.0f, -1.5f));

        // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        // shader1.setMat4("model", model);
        // shader3.setFloat4("ourColor", greenValue, greenValue - 0.1f, moveValue - 0.2f);
        // glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // VAO1.unBind();
        // VAO2.bind();

        // model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
        // trans = glm::rotate(trans, glm::radians(-moveValue * 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // shader1.setMat4("transform", model);
        // glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // VAO2.unBind();

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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void processInput(GLFWwindow* window, glm::vec3 direction) {
    const float cameraSpeed = 2.5f * deltaTime;
    const float antSpeed = 1.0f * deltaTime;
    const float rotationSpeed = 5.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        opacity += 0.0001f;

        if (opacity >= 1.0f) {
            opacity = 1.0f;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        opacity -= 0.0001f;

        if (opacity <= 0.0f) {
            opacity = 0.0f;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationZ += rotationSpeed;

    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationZ -= rotationSpeed;

    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        offsetY += (direction.y * antSpeed);
        offsetX += (direction.x * antSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        offsetY += (direction.y * antSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        offsetY -= antSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        offsetX += (direction.y * antSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        offsetX -= antSpeed;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

bool testAABB(AABB* a, AABB* b) {
    // if this is negative they have collided
    float d1x = b->min.x - a->max.x;
    float d1y = b->min.y - a->max.y;
    float d2x = a->min.x - b->max.x;
    float d2y = a->min.y - b->max.y;

    // if the value is not negative, no collision
    if (d1x > 0.0f || d1y > 0.0f) {
        return false;
    }

    if (d2x > 0.0f || d2y > 0.0f) {
        return false;
    }

    return true;
}