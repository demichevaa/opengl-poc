#include "window.h"
#include "assets.h"
#include "level.h"
#include "game.h"

float WINDOW_WIDTH = 1366;
float WINDOW_HEIGHT = 768;

//int LEVEL_1_DATA[7][13] = {
//        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,},
//        {5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 5, 5, 5, },
//        {5, 2, 5, 2, 5, 1, 1, 2, 1, 1, 5, 2, 5, },
//        {4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, },
//        {4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, },
//        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, },
//        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, }
//};

int main() {
        GLFWwindow *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

        Sprite sprite;
        spriteCreateFromAssets(&sprite, "tst", "textures/block.png");

        sprite.X = 100;
        sprite.Y = 100;
        spriteApplyModel(&sprite);
//        Level level_1;
//        levelInitialize(&level_1, 7, 13, LEVEL_1_DATA);

        Game game;
        gameInitialize(&game);

        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                gameLoop(&game);
                //levelRender(&level_1);
                //spriteRender(&sprite);
                glfwSwapBuffers(window);
        }

        spriteRelease(&sprite);
        return EXIT_SUCCESS;
}
