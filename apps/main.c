#include "window.h"
#include "assets.h"
#include "level.h"

float WINDOW_WIDTH = 768;
float WINDOW_HEIGHT = 432;

int LEVEL_1_DATA[8][15] = {
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,},
        {4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4,},
        {4, 1, 4, 1, 4, 0, 0, 1, 0, 0, 4, 1, 4, 1,},
        {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3,},
        {3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,}
};

int main() {
        GLFWwindow *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

        Sprite sprite;
        spriteCreateFromAssets(&sprite, "tst", "textures/block.png");

        Level level_1;
        levelInitialize(&level_1, 8, 14, LEVEL_1_DATA);

        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                levelRender(&level_1);
                //spriteRender(&sprite);
                glfwSwapBuffers(window);
        }

        spriteRelease(&sprite);
        return EXIT_SUCCESS;
}
