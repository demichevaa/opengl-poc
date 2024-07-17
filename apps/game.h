#ifndef OPENGL_POC_APPS_GAME_H_
#define OPENGL_POC_APPS_GAME_H_

#include "block.h"
#include "level.h"
#include "ui.h"
#include "platform.h"
#include "input.h"
#include "ball.h"
#include "collision.h"

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
int game_loop(Game *p_game, GLFWwindow *p_window, float timeDelta);
int game_handle_input(Game *p_game, enum Actions action, float time_delta);

#endif //OPENGL_POC_APPS_GAME_H_
