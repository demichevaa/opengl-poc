#include "window.h"
#include "game.h"

float WINDOW_WIDTH = 1366;
float WINDOW_HEIGHT = 768;


int main() {
        GLFWwindow *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);


        struct GameState game;
        game_initialize(&game);

        //glfwSetWindowUserPointer(window, &game);
        //glfwSetKeyCallback(window, inputCallback);

        float delta_time = 0.0f;
        float last_frame = 0.0f;
        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                float current_frame = (float)glfwGetTime();
                delta_time = current_frame - last_frame;
                last_frame = current_frame;

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                game_loop(&game, window, delta_time);
                glfwSwapBuffers(window);
        }

        return EXIT_SUCCESS;
}
