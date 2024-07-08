#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stb_image.h>

#include <stdlib.h>
#include <stdio.h>
#include "window.h"

// Window dimensions

// Vertex shader source code
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec2 texCoords;\n"
                                   "out vec2 TexCoords;\n"
                                   "uniform mat4 MVP;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = MVP * vec4(position, 1.0);\n"
                                   "    TexCoords = texCoords;\n"
                                   "}\0";

// Fragment shader source code
const GLchar* fragmentShaderSource = "#version 330 core\n"
                                     "in vec2 TexCoords;\n"
                                     "out vec4 color;\n"
                                     "uniform sampler2D ourTexture;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    color = texture(ourTexture, TexCoords);\n"
                                     "}\0";

// Screen size
const float screenWidth = 768;  // Get the actual screen width
const float screenHeight = 432; // Get the actual screen height
const float screenAspect = screenWidth / screenHeight;

void mat4_mul(mat4 a, mat4 b, mat4 result) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        result[i][j] = 0.0f;
                        for (int k = 0; k < 4; k++) {
                                result[i][j] += a[i][k] * b[k][j];
                        }
                }
        }
}

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int debugMat4Print(mat4 mat) {
        for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                        printf("%7.4g\t", mat[i][j]);
                }
                printf("\n");
        }

        return EXIT_SUCCESS;
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);

        // Initialize GLAD to setup the OpenGL Function pointers
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glViewport(0, 0, screenWidth, screenHeight);

        // Build and compile our shader program
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

        int success;
        char infoLog[1024];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
                fprintf(stderr, "ERROR::Shader::Linking:\n%s", infoLog);
                exit(EXIT_FAILURE);
        }


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Set up vertex data (and buffer(s)) and attribute pointers
        GLfloat vertices[] = {
            // Positions          // Texture Coords
            1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // Top Right
            1.0f, 0.0f,  0.0f,  1.0f, 0.0f,   // Bottom Right
            0.0f, 0.0f,  0.0f,  0.0f, 0.0f,   // Bottom Left
            0.0f,  1.0f, 0.0f,   0.0f, 1.0f    // Top Left
        };
        GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,   // First Triangle
            1, 2, 3    // Second Triangle
        };
        GLuint VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO

        // Load and create a texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load, create texture and generate mipmaps
        int width, height, nrChannels;
        unsigned char* image = stbi_load("/home/demichevaa/CLionProjects/opengl-poc/assets/textures/block_2.png", &width, &height, &nrChannels, 0);
        if (image)
        {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
                glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
                printf("Failed to load texture\n");
        }
        stbi_image_free(image);

        mat4 model, view, _projection, MVP, _scale, translate, rotate;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(_projection);
        glm_mat4_identity(_scale);
        glm_mat4_identity(translate);
        glm_mat4_identity(rotate);

        _scale[0][0] = 10;
        _scale[1][1] = 10;

        translate[0][3] = 0;
        translate[1][3] = 0;

        mat4 tmp;
        mat4_mul(rotate, _scale, tmp);
        mat4_mul(translate, tmp, model);

        printf("Model:\n");
        debugMat4Print(model);


        float aspect_ratio = 16.0f/9.0f;
        float ORIGIN_WIDTH = 0;
        float ORIGIN_HEIGHT = 0;
        float SCREEN_WIDTH = 160;
        float SCREEN_HEIGHT = 90;
        float Z_FAR = 1;
        float Z_NEAR = -1;

        _projection[0][0] = 2 / (SCREEN_WIDTH - ORIGIN_WIDTH);
        _projection[1][1] = 2 / (SCREEN_HEIGHT - ORIGIN_HEIGHT);
        _projection[2][2] = 2 / (Z_FAR - Z_NEAR);
        _projection[0][3] = - (SCREEN_WIDTH + ORIGIN_WIDTH) / (SCREEN_WIDTH - ORIGIN_WIDTH);
        _projection[1][3] = - (SCREEN_HEIGHT + ORIGIN_HEIGHT) / (SCREEN_HEIGHT - ORIGIN_HEIGHT);
        _projection[2][3] = - (Z_FAR + Z_NEAR) / (Z_FAR - Z_NEAR);

        printf("Projection:\n");
        debugMat4Print(_projection);

        mat4_mul(_projection, model, MVP);
        glm_mat4_transpose(MVP);

        printf("MVP:\n");
        debugMat4Print(MVP);

        while (!glfwWindowShouldClose(window))
        {

                // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
                glfwPollEvents();

                // Render
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                //glClear(GL_COLOR_BUFFER_BIT);

                // Bind Texture
                glBindTexture(GL_TEXTURE_2D, texture);

                // Activate shader
                glUseProgram(shaderProgram);

                // Create transformations


                //glm_ortho(offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f, projection);
//                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//                glClear(GL_COLOR_BUFFER_BIT);
                //glDisable(GL_SCISSOR_TEST);


                //glm_ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f, projection);
                // Get their uniform location
                GLint modelLoc = glGetUniformLocation(shaderProgram, "MVP");

                // Pass them to the shaders
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)MVP);

                // Draw container
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);


                // Swap the screen buffers
                glfwSwapBuffers(window);
        }

        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);

        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate();
        return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
}
