#include "ball.h"

struct Ball ball_create() {
        struct ShaderProgram *shader = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(shader, "shaders/ball.vertex.glsl", "shaders/ball.fragment.glsl", NULL);

        struct Texture2D *texture = malloc(sizeof(struct Texture2D));
        texture_create_from_assets(texture, "textures/item_106.png");


        struct Ball ball;
        sprite_initialize(&ball.sprite, shader, texture);
        ball.position[0] = VIEWPORT_WIDTH / 2;
        ball.position[1] = VIEWPORT_HEIGHT / 2;
        glm_vec2_copy((float *) &DIRECTION.SW, ball.direction);
        ball.damage = 1;

        ball.speed = 40.0f;
        ball.radius = 2.0f;
        ball.sprite.width = ball.radius * 2;
        ball.sprite.height = ball.radius * 2;

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
        sprite_render(&p_ball->sprite, NULL);

        return EXIT_SUCCESS;
}

int ball_on_hit_platform(struct Ball *p_ball, struct Platform *p_platform) {
        //vec2_invert(p_ball->direction);
        //p_ball->direction[1] *= -1;
        vec2_invert(p_ball->direction, Y_AXIS);
        //glm_vec2_mul(p_ball->direction, DIRECTION.NW, p_ball->direction);

        ball_log(p_ball);
        return EXIT_SUCCESS;
}

int ball_on_hit_block(struct Ball *p_ball, struct Block *p_block) {
        p_block->health -= p_ball->damage;
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
                "[BALL:STATE] -> position(%.2fx%.2f), direction(%.2fx%.2f), speed(%.0f)\n",
                p_ball->position[0],
                p_ball->position[1],
                p_ball->direction[0],
                p_ball->direction[1],
                p_ball->speed
        );

        return EXIT_SUCCESS;
}