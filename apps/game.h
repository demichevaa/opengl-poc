#ifndef OPENGL_POC_APPS_GAME_H_
#define OPENGL_POC_APPS_GAME_H_

#include "block.h"
#include "level.h"

typedef enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
} GameState;

typedef struct Game {
        GameState state;
        Sprite background;
        Level level;
} Game;


int gameInitialize(Game *pGame);
int gameLoop(Game *pGame);

#endif //OPENGL_POC_APPS_GAME_H_
