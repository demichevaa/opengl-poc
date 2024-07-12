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

int backgroundInitialize() {

}

int gameInitialize(Game *pGame) {
        Level level_1;
        levelInitialize(&level_1, 7, 13, LEVEL_1_DATA);

        spriteCreateFromAssets(&pGame->background, "background", "textures/black_background_56.png");
        pGame->background.height = 10;
        pGame->background.width = 10;

        pGame->level = level_1;
        pGame->state = GAME_ACTIVE;

        EXIT_SUCCESS;
}

int gameLoop(Game *pGame) {
        switch (pGame->state) {
                case GAME_ACTIVE:
                        spriteRender(&pGame->background);
                        levelRender(&pGame->level);

                        break;
                case GAME_MENU:
                case GAME_WIN:
                default:
                        break;
        }

        EXIT_SUCCESS;
}

