#ifndef OPENGL_POC_APPS_GAME_H_
#define OPENGL_POC_APPS_GAME_H_

#include "block.h"
#include "level.h"
#include "ui.h"
#include "platform.h"
#include "input.h"
#include "ball.h"

typedef enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
} GameState;

typedef struct Game {
        GameState state;
        Sprite background;
        struct Ball ball;
        UI ui;
        Level level;
        struct Platform platform;
} Game;

int gameInitialize(Game *pGame);
int gameLoop(Game *p_game, GLFWwindow *p_window, float timeDelta);
int gameHandleInput(Game *p_game, enum Actions action, float timeDelta);

#endif //OPENGL_POC_APPS_GAME_H_
