#ifndef OPENGL_POC_APPS_GAME_H_
#define OPENGL_POC_APPS_GAME_H_

#include "block.h"
#include "level.h"
#include "ui.h"
#include "platform.h"
#include "input.h"
#include "ball.h"
#include "collision.h"

enum GameStatus {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
};

struct GameState {
        enum GameStatus status;

        struct Platform platform;
        size_t platform_id;
        size_t ball_id;
        size_t level_id;
        struct Ball ball;
        struct UI ui;
        struct Level level;
};

int game_initialize(struct GameState *p_state);
int game_loop(struct GameState *p_state, GLFWwindow *p_window, float time_delta);
int game_handle_input(struct GameState *p_state, enum Actions action, float time_delta);

#endif //OPENGL_POC_APPS_GAME_H_
