#include "game.h"

int LEVEL_1_DATA[7][13] = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,},
        {5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 5, 5, 5, },
        {5, 2, 5, 2, 5, 1, 1, 2, 1, 1, 5, 2, 5, },
        {4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, },
        {4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, },
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, },
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, }
};

int gameInitialize(Game *pGame) {
        Level level_1;
        levelInitialize(&level_1, 7, 13, LEVEL_1_DATA);

        spriteCreateFromAssets(&pGame->background, "background", "textures/black_background_56.png");
        pGame->background.height = 10;
        pGame->background.width = 10;

        uiInitialize(&pGame->ui);

        pGame->platform = platformCreate();
        pGame->ball = ballCreate();
        pGame->level = level_1;
        pGame->state = GAME_ACTIVE;


        EXIT_SUCCESS;
}


enum Actions getAction(GLFWwindow *p_window) {
        if (glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                return LEFT;
        }
        if (glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                return RIGHT;
        }
        return IDLE;
}

int gameLoop(Game *p_game, GLFWwindow *p_window, float timeDelta) {
        switch (p_game->state) {
                case GAME_ACTIVE:
                        gameHandleInput(p_game, getAction(p_window), timeDelta);
                        uiRender(&p_game->ui);
                        levelRender(&p_game->level);
                        platformRender(&p_game->platform, timeDelta);
                        ballRender(&p_game->ball, timeDelta);
                        break;
                case GAME_MENU:
                case GAME_WIN:
                default:
                        break;
        }

        EXIT_SUCCESS;
}

int gameHandleInput(Game *p_game, enum Actions action, float timeDelta) {
        platformHandleInput(&p_game->platform, action, timeDelta);
        return EXIT_SUCCESS;
}