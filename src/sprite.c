#include "sprite.h"
#include "viewport.h"

float SPRITE_VERTICES[] = {
    -0.5f, -0.5f,       0.0f, 0.0f,
    0.5f, -0.5f,          1.0f, 0.0f,
    -0.5f, 0.5f,          0.0f, 1.0f,
    0.5f, 0.5f,           1.0f, 1.0f,
};
unsigned int SPRITE_INDICES[] = {
    0, 1, 2,
    2, 1, 3,
};



int spriteSetOrthogonalProjection(Sprite *sprite, float left, float right, float bottom, float top);

int spriteInitialize(Sprite *sprite,
                     const char *tag,
                     ShaderProgram *shader,
                     Texture2D *texture) {
        sprite->tag = tag;
        sprite->shader = shader;
        sprite->texture = texture;

        glm_mat4_identity(sprite->model);

        glGenVertexArrays(1, &sprite->VAO);
        glGenBuffers(1, &sprite->VBO);
        glGenBuffers(1, &sprite->EBO);

        glBindVertexArray(sprite->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_VERTICES), SPRITE_VERTICES, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SPRITE_INDICES), SPRITE_INDICES, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        shaderProgramUse(sprite->shader);
//        10	0	0	0
//        0	10	0	0
//        0	0	0	0
//        10	10	0	1

//        shaderSetInt(sprite->shader, "image", 0);
//        vec3 color = {0.80f, 0.05f, 0.18f};
//        shaderSetVec3f(sprite->shader, "color", &color);

        vec2 defaultPosition = {0.0f, 0.0f};
        vec2 defaultScale = {1.0f, 1.0f};

        viewportSetOrthogonalProjection(&sprite->projection);
        glm_scale(sprite->model, (vec3){100.0f, 100.0f, 1.0f});
        spriteSetPosition(sprite, defaultPosition);


        //spriteSetRotationAngle(sprite, 90.0f);
        //spriteSetOrthogonalProjection(sprite, 0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

//        spriteSetPosition(sprite, defaultPosition);
//        spriteSetScale(sprite, defaultScale);


        spriteApplyModel(sprite);

        //shaderSetFloat(sprite->shader, "aspectRatio", SCREEN_ASPECT_RATIO);

        return EXIT_SUCCESS;
}

int spriteRender(Sprite *sprite) {

        glActiveTexture(GL_TEXTURE0);
        textureBind(sprite->texture);

        shaderProgramUse(sprite->shader);

        glBindVertexArray(sprite->VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        return EXIT_SUCCESS;
}

int spriteRelease(Sprite *sprite) {
        free(sprite->shader);
        free(sprite->texture);

        glDeleteVertexArrays(1, &sprite->VAO);
        glDeleteBuffers(1, &sprite->EBO);
        glDeleteBuffers(1, &sprite->VBO);

        sprite->shader = NULL;
        sprite->texture = NULL;
        sprite->VAO = INT_MAX;
        sprite->EBO = INT_MAX;
        sprite->VBO = INT_MAX;

        printf("[SPRITE:RELEASE] -> Sprite `%s` destroyed", sprite->tag);
        sprite = NULL;

        return EXIT_SUCCESS;
}

int spriteApplyModel(Sprite *sprite) {

        shaderSetMat4(sprite->shader, "projection", &sprite->projection);
        shaderSetMat4(sprite->shader, "model", &sprite->model);

        printf("model:\n");
        debugMat4Print(sprite->model);
        printf("projection:\n");
        debugMat4Print(sprite->projection);

        return EXIT_SUCCESS;
}

int spriteSetPosition(Sprite *sprite, const vec2 position) {
        glm_translate(sprite->model, (vec3){position[0], position[1], 0.0f});

        sprite->position[0] = position[0];
        sprite->position[1] = position[1];

        return EXIT_SUCCESS;
}
