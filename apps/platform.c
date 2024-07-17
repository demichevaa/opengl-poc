#include "platform.h"
#include "common.h"

struct Platform platform_create() {
        struct ShaderProgram *program = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(program, "shaders/platform.vertex.glsl", "shaders/platform.fragment.glsl", NULL);

        struct Texture2D *texture = malloc(sizeof(struct Texture2D));
        texture_create_from_assets(texture, "textures/paddle.png");

        struct Platform platform;
        sprite_initialize(&platform.sprite, program, texture);
        platform.size = 35.0f;
        platform.sprite.width = platform.size;
        platform.sprite.height = 3;

        platform.position[0] = VIEWPORT_WIDTH / 2;
        platform.position[1] = 2.0f;
        platform.velocity = 35.0f;

        return platform;
}

int platform_render(struct Platform *p_platform, float time_delta) {
        sprite_set_position(&p_platform->sprite, p_platform->position);
        sprite_render(&p_platform->sprite, NULL);

        return EXIT_SUCCESS;
}

int platform_handle_input(struct Platform *p_platform, enum Actions action, float time_delta) {
        switch (action) {
                case LEFT:
                        p_platform->position[0] -= p_platform->velocity * time_delta;
                        break;
                case RIGHT:
                        p_platform->position[0] += p_platform->velocity * time_delta;
                        break;
                default:
                        break;
        }
        clamp_to_viewport(p_platform->position, p_platform->sprite.width, p_platform->sprite.height);

        return EXIT_SUCCESS;
}
