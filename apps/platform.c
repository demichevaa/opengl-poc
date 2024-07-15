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

        platform.x = VIEWPORT_WIDTH / 2;
        platform.y = 2.0f;
        platform.velocity = 35.0f;

        return platform;
}

int platformRender(struct Platform *p_platform, float timeDelta) {
        float centerAdjustment = p_platform->sprite.width / 2.0f;
        p_platform->sprite.X = (p_platform->x - centerAdjustment);

        spriteSetPosition(&p_platform->sprite, (vec2){p_platform->x, p_platform->y});
        spriteRender(&p_platform->sprite, NULL);

        return EXIT_SUCCESS;
}

int platformHandleInput(struct Platform *p_platform, enum Actions action, float timeDelta) {
        float edgeDistance = p_platform->size / 2.0f;

        switch (action) {
                case LEFT:
                        if (p_platform->x - edgeDistance > VIEWPORT_ORIGIN) {
                                p_platform->x -= p_platform->velocity * timeDelta;
                        }
                        break;

                case RIGHT:
                        if (p_platform->x + edgeDistance < VIEWPORT_WIDTH) {
                                p_platform->x += p_platform->velocity * timeDelta;
                        }
                        break;

                default:
                        break;
        }

        return EXIT_SUCCESS;
}
