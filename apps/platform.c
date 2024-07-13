#include "platform.h"
#include "assets.h"

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
        platform.velocity = 2.0f;

        return platform;
}

int platformRender(struct Platform *p_platform, float timeDelta) {
        float centerAdjustment = p_platform->sprite.width / 2.0f;
        p_platform->sprite.X = (p_platform->x - centerAdjustment);

        spriteRender(&p_platform->sprite, NULL);

        return EXIT_SUCCESS;
}

int platformHandleInput(struct Platform *p_platform, int key, int action) {
        if (key == GLFW_KEY_LEFT) {
                p_platform->x -= p_platform->velocity;
        }
        else if (key == GLFW_KEY_RIGHT) {
                p_platform->x += p_platform->velocity;
        }
        else {

        }
        return EXIT_SUCCESS;
}
