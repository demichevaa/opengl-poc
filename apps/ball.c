#include "ball.h"

struct Ball ballCreate() {
        ShaderProgram *program = malloc(sizeof(ShaderProgram));
        shaderCreateFromAssets(program, "shaders/ball.vertex.glsl", "shaders/ball.fragment.glsl", NULL);

        Texture2D *texture = malloc(sizeof(Texture2D));
        textureCreateFromAssets(texture,  "textures/item_106.png");


        struct Ball ball;
        spriteInitialize(&ball.sprite, "ball", program, texture);
        ball.position[0] = VIEWPORT_WIDTH / 2;
        ball.position[1] = VIEWPORT_HEIGHT / 2;
        glm_vec2_copy(DIRECTION.Bottom, &ball.direction);
        ball.damage = 1;

        ball.velocity[0] = 1.0f;
        ball.velocity[1] = 1.0f;

        ball.speed = 20.0f;
        ball.radius = 3.0f;
        ball.sprite.width = ball.radius * 2;
        ball.sprite.height = ball.radius * 2;

        return ball;
}

int ballProcess(struct Ball *p_ball, float timeDelta) {
        vec2 velocity, position;

        glm_vec2_scale(p_ball->direction, p_ball->speed, velocity);
        glm_vec2_scale(velocity, timeDelta, velocity);
        glm_vec2_add(p_ball->position, velocity, position);
        clampToViewport(position, p_ball->radius * 2, p_ball->radius * 2);
        glm_vec2_copy(position,p_ball->position);

        return EXIT_SUCCESS;
}

int ballRender(struct Ball *p_ball, float timeDelta) {
        ballProcess(p_ball, timeDelta);
        spriteSetPosition(&p_ball->sprite, p_ball->position);
        spriteRender(&p_ball->sprite, NULL);

        return EXIT_SUCCESS;
}

