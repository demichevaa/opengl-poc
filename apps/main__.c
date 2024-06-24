#include "window.h"
#include "assets.h"
#include "game.h"


void processInput(GLFWwindow *window);

int main() {
        int level_data[8][15] = {
            {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
            {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
            {4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
            {4, 1, 4, 1, 4, 0, 0, 1, 0, 0, 4, 1, 4, 1, 4},
            {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
            {3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3},
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
        };

        GLFWwindow *window = create_window("opengl-app", SCREEN_WIDTH, SCREEN_HEIGHT);

        Level level_debug;
        levelInitialize(&level_debug, 8, 15, level_data);
        for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 15; ++j) {
                        printf("%d ", level_debug.blocks[i][j].value);
                }
                printf("\n");
        }

        Sprite sprite;
        spriteCreateFromAssets(&sprite, "debug", "textures/block.png");

        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                //levelRender(&level_debug);

                spriteRender(&sprite);
                glfwSwapBuffers(window);

                glfwPollEvents();

        }

        spriteRelease(&sprite);
        glfwTerminate();

        return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, 1);
}
