#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stb_image.h>

#include <stdlib.h>
#include <stdio.h>
#include "viewport.h"

// Window dimensions

// Vertex shader source code
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec2 texCoords;\n"
                                   "out vec2 TexCoords;\n"
                                   "uniform mat4 model;\n"
                                   "uniform mat4 projection;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = projection * model * vec4(position, 1.0);\n"
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

//// Game units
//const float GAME_WIDTH = 160.0f;
//const float GAME_HEIGHT = 90.0f;
//const float GAME_ASPECT = GAME_WIDTH / GAME_HEIGHT;

// Screen size
const float screenWidth = 640;  // Get the actual screen width
const float screenHeight = 480; // Get the actual screen height
const float screenAspect = screenWidth / screenHeight;


int ortho(mat4 *matrix, float left, float right, float bottom, float top, float near, float far) {
        glm_mat4_identity(*matrix);

        (*matrix)[0][0] = 2 / (right - left);
        (*matrix)[1][1] = 2 / (top - bottom);
        (*matrix)[2][2] = -2 / (far - near);

        (*matrix)[0][3] = -(right + left) / (right - left);
        (*matrix)[1][3] = -(top + bottom) / (top - bottom);
        (*matrix)[2][3] = -(far + near) / (far - near);

        (*matrix)[3][3] = 1;


        return EXIT_SUCCESS;
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
        // Calculate scale factor
        float scale;
        if (screenAspect > GAME_ASPECT) {
                // Screen is wider than game, fit game height to screen height
                scale = screenHeight / GAME_HEIGHT;
        } else {
                // Screen is narrower than game, fit game width to screen width
                scale = screenWidth / GAME_WIDTH;
        }

        // Calculate game size on screen
        float gameWidthOnScreen = GAME_WIDTH * scale;
        float gameHeightOnScreen = GAME_HEIGHT * scale;

        // Calculate offsets for centering the game on the screen
        float offsetX = (screenWidth - gameWidthOnScreen) / 2.0f;
        float offsetY = (screenHeight - gameHeightOnScreen) / 2.0f;

        // Init GLFW
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

        // Define the viewport dimensions
        //glViewport(0, 0, WIDTH, HEIGHT);

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

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Set up vertex data (and buffer(s)) and attribute pointers
        GLfloat vertices[] = {
            // Positions          // Texture Coords
            1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // Top Right
            1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // Bottom Left
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f    // Top Left
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

        glViewport(offsetX, offsetY, gameWidthOnScreen, gameHeightOnScreen);
        glScissor(offsetX, offsetY, gameWidthOnScreen, gameHeightOnScreen);
        glEnable(GL_SCISSOR_TEST);

        mat4 model;
        glm_mat4_identity(model);
        debugMat4Print(model);

        vec4 spriteSpawn = {0.0f, 0.0f, 0.0f, 0.0f};
        vec4 spriteScale = {160.0f, 90.0f, 0.0f, 0.0f};

        vec2 currentPos = {model[3][0], model[3][1]};

        float x, y;
        x = spriteSpawn[0] - currentPos[0];
        y = spriteSpawn[1] - currentPos[1];
        glm_translate(model, (vec4){x, y, 0.0f, 0.0f});
        printf("Translate 2\n");
        debugMat4Print(model);

        glm_scale(model, spriteScale);
        printf("Scale\n");
        debugMat4Print(model);
//
//        glm_translate(model, (vec2){10.0f, 10.0f});
//        printf("Translate 2\n");
//        debugMat4Print(model);


        //glm_scale(model, (vec3){30.0f, 30.0f, 0.0f}); // Scale uniformly



        mat4 projection;
        float left, right, top, bottom;
        float unitInPixels = screenWidth / GAME_WIDTH;
        left = 0;//-(unitInPixels * GAME_WIDTH);
        right = (unitInPixels * GAME_WIDTH) / 2;
        top = unitInPixels * GAME_HEIGHT / 2;
        bottom = 0;//-unitInPixels * GAME_HEIGHT;
        //glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projection);
        glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projection);

        //ortho(&projection, offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f);

        //glm_ortho(offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f, projection);
        printf("Projection\n");
        debugMat4Print(projection);
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
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                //glDisable(GL_SCISSOR_TEST);


                //glm_ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f, projection);
                // Get their uniform location
                GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
                GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

                // Pass them to the shaders
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)projection);

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
