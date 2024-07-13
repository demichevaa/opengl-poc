#ifndef OPENGL_POC_APPS_GAME_H_
#define OPENGL_POC_APPS_GAME_H_

#include "block.h"
#include "level.h"
#include "ui.h"
#include "platform.h"

typedef enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
} GameState;

typedef struct Game {
        GameState state;
        Sprite background;
        UI ui;
        Level level;
        struct Platform platform;
} Game;


int gameInitialize(Game *pGame);
int renderLoop(Game *p_game, float timeDelta);
int gameHandleInput(Game *p_game, int key, int action);

#endif //OPENGL_POC_APPS_GAME_H_
