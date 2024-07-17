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

int game_detect_collisions(struct GameState *p_state);
typedef int (*LevelCallback)(struct GameState *p_state, struct Block *p_block);
int game_for_each_active_block(struct GameState *p_state, LevelCallback handleBlock);
int handle_ball_collision(struct GameState *p_state, struct Block *p_block);

int game_initialize(struct GameState *p_state) {
        struct Level level_1;
        level_initialize(&level_1, 7, 13, LEVEL_1_DATA);


        ui_initialize(&p_state->ui);

        p_state->platform = platform_create();
        p_state->ball = ball_create();
        p_state->level = level_1;
        p_state->status = GAME_ACTIVE;

        EXIT_SUCCESS;
}


enum Actions get_player_action(GLFWwindow *p_window) {
        if (glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                return LEFT;
        }
        if (glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                return RIGHT;
        }
        return IDLE;
}


int game_loop(struct GameState *p_state, GLFWwindow *p_window, float time_delta) {
        switch (p_state->status) {
                case GAME_ACTIVE:
                        game_handle_input(p_state, get_player_action(p_window), time_delta);

                        ball_update(&p_state->ball, time_delta);


                        ui_render(&p_state->ui);
                        level_render(&p_state->level);

                        platform_render(&p_state->platform, time_delta);
                        ball_render(&p_state->ball, time_delta);
                        game_detect_collisions(p_state);

                        break;
                case GAME_MENU:
                case GAME_WIN:
                default:
                        break;
        }

        EXIT_SUCCESS;
}

int game_handle_input(struct GameState *p_state, enum Actions action, float time_delta) {
        platform_handle_input(&p_state->platform, action, time_delta);

        return EXIT_SUCCESS;
}

int game_detect_collisions(struct GameState *p_state) {
        struct Ball *p_ball = &p_state->ball;
        bool is_platform_hit = collision_check_ABBB(&p_state->platform.sprite, &p_ball->sprite);
        bool is_wall_hit = collision_check_x(&p_ball->sprite, VIEWPORT_ORIGIN, VIEWPORT_WIDTH);

        if (is_platform_hit) {
                ball_on_hit_platform(&p_state->ball, &p_state->platform);
                return EXIT_SUCCESS;
        }
        if (is_wall_hit) {
                ball_on_hit_wall(p_ball);
                return EXIT_SUCCESS;
        }


        return game_for_each_active_block(p_state, handle_ball_collision);
}

int handle_ball_collision(struct GameState *p_state, struct Block *p_block) {
        bool is_block_hit = collision_check_ABBB(&p_block->sprite, &p_state->ball.sprite);
        if (is_block_hit) {
                ball_on_hit_block(&p_state->ball, p_block);
                return EXIT_SUCCESS;
        }

        return EXIT_FAILURE;
}

int game_for_each_active_block(struct GameState *p_state, LevelCallback handleBlock) {
        if (handleBlock == NULL) {
                return EXIT_FAILURE;
        }

        struct Level *p_level = &p_state->level;

        for (int i = 0; i < p_level->rows_count; ++i) {
                for (int j = 0; j < p_level->columns_count; ++j) {
                        struct Block *p_block = &p_level->blocks[i][j];
                        if (p_block == NULL || p_block->is_dead) {
                                continue;
                        }

                        if (handleBlock(p_state, p_block) == EXIT_SUCCESS) {
                                return EXIT_SUCCESS;
                        }
                }
        }
        return EXIT_SUCCESS;
}
