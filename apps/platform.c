#include "platform.h"
#include "common.h"

struct Platform platformCreate() {
        ShaderProgram *program = malloc(sizeof(ShaderProgram));
        shaderCreateFromAssets(program, "shaders/platform.vertex.glsl", "shaders/platform.fragment.glsl", NULL);

        Texture2D *texture = malloc(sizeof(Texture2D));
        textureCreateFromAssets(texture,  "textures/paddle.png");

        struct Platform platform;
        spriteInitialize(&platform.sprite, "platform", program, texture);
        platform.size = 35.0f;
        platform.sprite.width = platform.size;
        platform.sprite.height = 3;

        platform.position[0] = VIEWPORT_WIDTH / 2;
        platform.position[1] = 2.0f;
        platform.velocity = 35.0f;

        return platform;
}

int platformRender(struct Platform *p_platform, float timeDelta) {
        spriteSetPosition(&p_platform->sprite, p_platform->position);
        spriteRender(&p_platform->sprite, NULL);

        return EXIT_SUCCESS;
}

int platformHandleInput(struct Platform *p_platform, enum Actions action, float timeDelta) {
        switch (action) {
                case LEFT:
                        p_platform->position[0] -= p_platform->velocity * timeDelta;

                        break;

                case RIGHT:
                        p_platform->position[0] += p_platform->velocity * timeDelta;

                        break;

                default:
                        break;
        }

        clampToViewport(p_platform->position, p_platform->sprite.width, p_platform->sprite.height);


        return EXIT_SUCCESS;
}
