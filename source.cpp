#include "glad.c"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


const char* vertexShaderSource =
// Version
"#version 330 core \n"

// Attributes
"layout(location = 0) in vec3 aPos; \n"
"layout(location = 1) in vec3 aColor; \n"
"layout(location = 2) in vec2 aUV;"

// Variables
"out vec3 ourColor; \n"
"out vec3 normal;\n"
//"out vec2 uv;\n"

// Uniforms
"uniform mat4 model; \n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

// Main function
"void main()\n"
"{\n"
"       gl_Position = projection * view * model * vec4(aPos, 1.0); \n"

"       ourColor = aColor; \n"
"       normal = aPos; \n"
//"       uv = aUV;"
"} \n";

const char* fragmentShaderSource =
// Version
"#version 330 core\n"

// Attributes
"out vec4 FragColor;\n"

// Variables
"in vec3 ourColor;\n"
"in vec3 normal;\n"
// "in vec2 uv;\n"

// Main functio
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n"
;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window and its context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Generate and bind the VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertex data to the VBO
    float vertices[] = {
        // Coordinates          Normals               Uv's
    
        // Front face
         -1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         1.0f, -1.0f, 1.0f,     0.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f, -1.0f, 1.0f,     0.0f, 0.0f, 1.0f,    // 1.0f, 1.0f    // Bottom right
         -1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f,    // 0.0f, 0.0f    // Top left
         -1.0f, -1.0f, 1.0f,    0.0f, 0.0f, 1.0f,    // 0.0f, 1.0f    // Bottom left
                                                     //
         // Back face                                //
         -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f,    // 0.0f, 1.0f,   // Bottom left
                                                     //
         // Left face                                //
         -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 1.0f,    // 0.0f, 1.0f,   // Bottom left
                                                     //
         // Right face                               //
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f,    // 0.0f, 1.0f,   // Bottom left
                                                     //
          // Top face                                //
         -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 1.0f,   // Bottom left
                                                     //
          // Bottom face                             //
         -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 0.0f,   // Top right
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 1.0f,    // 1.0f, 1.0f,   // Bottom right
         -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 0.0f,   // Top left
         -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    // 0.0f, 1.0f,    // Bottom left
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shaders into a shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteShader(fragmentShader);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set the projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    unsigned int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    // Set the model matrix
    glm::mat4 model = glm::mat4(1.0f);
    unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    // Set the view matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    float angle = 0.0f;


    glm::vec3 cpos = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 ct = glm::vec3(0.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);


    // Declare the radius of the sphere (in this case, the radius is set to 5.0)
    float radius = 5.0f;

    // Declare the polar and azimuthal angles (in this case, the angles are set to 0.0)
    float theta = 0.0f;
    float phi = 0.0f;

    // Run the main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll for events
        glfwPollEvents();

        // Process input
        processInput(window);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            radius -= 1.0f / 250;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            radius += 1.0f / 250;
        }
        // If the LEFT arrow key is pressed, increment the polar angle
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            theta += 0.1f / 150;
        }

        // If the RIGHT arrow key is pressed, decrement the polar angle
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            theta -= 0.1f / 150;
        }

        // If the UP arrow key is pressed, increment the azimuthal angle
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            phi += 0.1f / 150;
        }

        // If the DOWN arrow key is pressed, decrement the azimuthal angle
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            phi -= 0.1f / 150;
        }

        // Convert the spherical coordinates to Cartesian coordinates
        float x = radius * sin(phi) * cos(theta);
        float y = radius * cos(phi);
        float z = radius * sin(phi) * sin(theta);

        // Update the camera position using the Cartesian coordinates
        cpos.x = x;
        cpos.y = y;
        cpos.z = z;

        // Set the "look at" point to the center of the sphere
        ct = glm::vec3(0.0f, 0.0f, 0.0f);

        // Create a view matrix using the updated camera position and look at point
        view = glm::lookAt(cpos, ct, up);


        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        // Update the angle of rotation

        // Create the rotation matrix
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0, 1.0, 1.0));

        // Apply the rotation to the model matrix
        model = rotation * model;

        // Update the model matrix uniform
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    // Delete the VAO, VBO, and shader program
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
