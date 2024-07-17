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
        glm_vec2_copy((float *) &DIRECTION.Bottom, ball.direction);
        ball.damage = 1;

        ball.speed = 30.0f;
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
        clamp_to_viewport(position, p_ball->radius * 2, p_ball->radius * 2);
        glm_vec2_copy(position,p_ball->position);

        return EXIT_SUCCESS;
}

int ball_render(struct Ball *p_ball, float time_delta) {
        spriteSetPosition(&p_ball->sprite, p_ball->position);
        sprite_render(&p_ball->sprite, NULL);

        return EXIT_SUCCESS;
}
