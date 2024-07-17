#include "window.h"
#include "game.h"

float WINDOW_WIDTH = 1366;
float WINDOW_HEIGHT = 768;


int main() {
        GLFWwindow *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);


        Game game;
        gameInitialize(&game);

        //glfwSetWindowUserPointer(window, &game);
        //glfwSetKeyCallback(window, inputCallback);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                float currentFrame = (float)glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                //printf("%f\n", deltaTime);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                game_loop(&game, window, deltaTime);
                glfwSwapBuffers(window);
        }

        return EXIT_SUCCESS;
}
