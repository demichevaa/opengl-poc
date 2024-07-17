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

int game_detect_collisions(Game *p_game);
typedef int (*LevelCallback)(Block *p_block, struct Ball *p_ball);
int level_for_each_active_block(Level *p_level, Callback callback);
int debug_callback(void *context);

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


enum Actions get_player_action(GLFWwindow *p_window) {
        if (glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                return LEFT;
        }
        if (glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                return RIGHT;
        }
        return IDLE;
}


int game_loop(Game *p_game, GLFWwindow *p_window, float timeDelta) {
        switch (p_game->state) {
                case GAME_ACTIVE:
                        game_handle_input(p_game, get_player_action(p_window), timeDelta);
                        uiRender(&p_game->ui);
                        levelRender(&p_game->level);

                        platformRender(&p_game->platform, timeDelta);
                        ballRender(&p_game->ball, timeDelta);
                        game_detect_collisions(p_game);

                        break;
                case GAME_MENU:
                case GAME_WIN:
                default:
                        break;
        }

        EXIT_SUCCESS;
}

int game_handle_input(Game *p_game, enum Actions action, float time_delta) {
        platformHandleInput(&p_game->platform, action, time_delta);

        return EXIT_SUCCESS;
}


int game_detect_collisions(Game *p_game) {
        bool is_platform_hit = collision_check_ABBB(&p_game->platform.sprite, &p_game->ball.sprite);

        if (is_platform_hit) {
                direction_invert(p_game->ball.direction);
                return EXIT_SUCCESS;
        }

        //level_for_each_active_block(&p_game->level, debug_callback);

//        Level *p_level = &p_game->level;
//        for (int i = 0; i < p_level->rowsCount; ++i) {
//                for (int j = 0; j < p_level->columnsCount; ++j) {
//                        Block *p_block = &p_level->blocks[i][j];
//
//                        if (p_block == NULL || p_block->is_dead) {
//                                continue;
//                        }
//
//                        bool is_block_hit = collision_check_ABBB(&p_block->sprite, &p_game->ball.sprite);
//                        if (is_block_hit) {
//                                block_on_hit(p_block, &p_game->ball);
//                                break;
//                        }
//                }
//
//        }

        return EXIT_SUCCESS;
}

int debug_callback(void *context) {
        has_collision = collision_check_ABBB(&p_block->sprite, &p_game->ball.sprite);
        printf("Callback\n");

        return EXIT_SUCCESS;
}

int level_for_each_active_block(Level *p_level,  LevelCallback callback) {
        if (callback == NULL) {
                return EXIT_FAILURE;
        }

        //bool has_collision = false;
        bool has_result = false;
        for (int i = 0; i < p_level->rowsCount; ++i) {
                for (int j = 0; j < p_level->columnsCount; ++j) {
                        Block *p_block = &p_level->blocks[i][j];
                        bool is_destroyed = p_block == NULL || p_block->is_dead;
                        if (is_destroyed) {
                                continue;
                        }

                        has_result = callback(p_block, );
                        if (has_result) {
                                break;
                        }
//                        has_collision = collision_check_ABBB(&p_block->sprite, &p_game->ball.sprite);
//                        if (has_collision) {
//                                block_on_hit(p_block, &p_game->ball);
//                                break;
//                        }
                }

                if (has_result) {
                        break;
                }

        }


        return EXIT_SUCCESS;
}

