#include "ball.h"
#include "register.h"
#include "collision.h"

struct Ball ball_create() {
        struct ShaderProgram *shader = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(shader, "shaders/ball.vertex.glsl", "shaders/ball.fragment.glsl", NULL);

        struct Texture2D *texture = malloc(sizeof(struct Texture2D));
        texture_create_from_assets(texture, "textures/item_106.png");


        struct Ball ball;
        ball.id = sequence_get_next();
        register_add(ball.id, &ball);

        sprite_initialize(&ball.sprite, shader, texture);
        ball.position[0] = VIEWPORT_WIDTH / 2;
        ball.position[1] = VIEWPORT_HEIGHT / 2;
        glm_vec2_copy((float *) &DIRECTION.SW, ball.direction);
        ball.damage = 1;

        ball.speed = 40.0f;
        ball.radius = 2.0f;
        ball.sprite.width = ball.radius * 2;
        ball.sprite.height = ball.radius * 2;

        ball_log(&ball);
        return ball;
}

int ball_update(struct Ball *p_ball, float time_delta) {
        vec2 velocity, position;

        glm_vec2_scale(p_ball->direction, p_ball->speed, velocity);
        glm_vec2_scale(velocity, time_delta, velocity);
        glm_vec2_add(p_ball->position, velocity, position);

        //clamp_to_viewport(position, p_ball->radius * 2, p_ball->radius * 2);
        glm_vec2_copy(position, p_ball->position);

        return EXIT_SUCCESS;
}

int ball_render(struct Ball *p_ball, float time_delta) {
        sprite_set_position(&p_ball->sprite, p_ball->position);
        sprite_render(&p_ball->sprite, NULL, NULL);

        return EXIT_SUCCESS;
}

int platform_get_edge_borders(struct Platform *p_platform, float out[2]) {
        float x_min = p_platform->position[0] - p_platform->size / 2.0f;
        float x_max = p_platform->position[0] + p_platform->size / 2.0f;

        float edge_hit_box_size = p_platform->size * p_platform->edge_hit_box_ratio;

        out[0] = x_min + edge_hit_box_size;
        out[1] = x_max - edge_hit_box_size;

        printf(
                "[PLATFORM:EDGES] -> left(%.2f), right(%.2f), position(%.2f)\n",
                out[0],
                out[1],
                p_platform->position[0]
        );

        return EXIT_SUCCESS;
}

int ball_on_hit_platform(struct Ball *p_ball, struct Platform *p_platform) {
        float edges_boards_pos[2];
        platform_get_edge_borders(p_platform, edges_boards_pos);

        bool is_ball_left_directed = p_ball->direction[0] < 0;
        bool is_ball_on_left_edge = p_ball->position[0] < edges_boards_pos[0];
        bool is_ball_on_right_edge = p_ball->position[0] > edges_boards_pos[1];
        bool is_edge_hit = is_ball_on_left_edge || is_ball_on_right_edge;
        bool is_ball_high = (p_ball->position[1] - p_ball->radius) > p_platform->position[1];
        bool is_aligned = (is_ball_left_directed && is_ball_on_left_edge) || (!is_ball_left_directed && is_ball_on_right_edge);


        ball_log(p_ball);
        platform_log(p_platform);
        printf(
                "[BALL:PLATFORM] -> is_ball_left_directed (%i), is_ball_on_left_edge(%i),"
                " is_ball_on_right_edge(%i), is_edge_hit(%i), is_ball_high(%i)\n",
                is_ball_left_directed,
                is_ball_on_left_edge,
                is_ball_on_right_edge,
                is_edge_hit,
                is_ball_high
        );

        if (!is_edge_hit || is_aligned) {
                return vec2_invert(p_ball->direction, Y_AXIS);
        }
        if (is_ball_high) {
                return vec2_invert(p_ball->direction, X_Y_AXES);
        }
        glm_vec2_copy(DIRECTION.SW, p_ball->direction);
        return EXIT_SUCCESS;
}

int ball_on_hit_block(struct Ball *p_ball, struct Block *p_block) {
        p_block->health -= p_ball->damage;

        bool is_ball_left_directed = p_ball->direction[0] < 0;
        //bool is_side_hit = collision_check_x()

        printf("[BLOCK:HIT] -> is_ball_left_directed(%i)\n", is_ball_left_directed);

        //TODO: full reflect on edge hit only
        vec2_invert(p_ball->direction, X_Y_AXES);

        printf("[BLOCK:HIT] -> Hit received. Hp: %i is_dead %i\n", p_block->health, p_block->is_dead);
        if (p_block->health <= 0) {
                p_block->is_dead = true;
                printf("[BLOCK:DESTROYED] -> Destroying block. Hp: %i is_dead %i\n", p_block->health, p_block->is_dead);
                sprite_free(&p_block->sprite);
        }

        return EXIT_SUCCESS;
}

int ball_on_hit_wall(struct Ball *p_ball) {
        vec2_invert(p_ball->direction, X_AXIS);


        return EXIT_SUCCESS;
}

int ball_log(struct Ball *p_ball) {
        printf(
                "[BALL:STATE] -> position(%.2f; %.2f), direction(%.2f; %.2f), speed(%.0f)\n",
                p_ball->position[0],
                p_ball->position[1],
                p_ball->direction[0],
                p_ball->direction[1],
                p_ball->speed
        );

        return EXIT_SUCCESS;
}