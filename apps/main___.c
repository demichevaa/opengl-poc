#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stb_image.h>

#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "assets.h"
#include "viewport.h"


const float screenWidth = 1366;  // Get the actual screen width
const float screenHeight = 768; // Get the actual screen height
const float screenAspect = screenWidth / screenHeight;

int main()
{
        Window window;
        windowInitialize(&window, "LearnOpenGL", screenWidth, screenHeight);


        Sprite sprite;
        spriteCreateFromAssets(&sprite, "debug", "textures/block_2.png");

        // Game loop
        while (!glfwWindowShouldClose(window.glfw_window))
        {
                glfwPollEvents();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // Bind Texture
                //glBindTexture(GL_TEXTURE_2D, texture);

                // Activate shader
                //glUseProgram(shaderProgram);

                // Create transformations
//                mat4 model;
//                glm_mat4_identity(model);
//                mat4 projection;
//                glm_ortho(0.0f, GAME_WIDTH, 0.0f, GAME_HEIGHT, -1.0f, 1.0f, projection);
//                glm_translate(model, (vec3){10.0f, 10.0f, 0.0f}); // Translate to the desired position
                //glm_scale(model, (vec3){GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, 1.0f}); // Scale to the desired size
//                glm_scale(model, (vec3){10.0f, 10.0f, 0.0f}); // Scale to the desired size


                //glm_ortho(offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f, projection);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                //glDisable(GL_SCISSOR_TEST);

                spriteRender(&sprite);

                //glm_ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f, projection);
                // Get their uniform location
//                GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
//                GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

                // Pass them to the shaders
//                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
//                glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)projection);

                // Draw container
//                glBindVertexArray(VAO);
//                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//                glBindVertexArray(0);

                // Swap the screen buffers
                glfwSwapBuffers(window.glfw_window);
        }

        spriteRelease(&sprite);
        glfwTerminate();

        return EXIT_SUCCESS;
}
