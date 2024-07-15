#include "sprite.h"

float SPRITE_VERTICES[] = {
        // Positions                            // Texture Coords
        1.0f,  1.0f,  0.0f,         1.0f, 1.0f,   // Top Right
        1.0f,  0.0f,  0.0f,         1.0f, 0.0f,   // Bottom Right
        0.0f,  0.0f,  0.0f,         0.0f, 0.0f,   // Bottom Left
        0.0f,  1.0f,  0.0f,         0.0f, 1.0f    // Top Left
};
unsigned int SPRITE_INDICES[] = {
        0, 1, 3,
        1, 2, 3
};

void mat4_mul(mat4 a, mat4 b, mat4 result) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        result[i][j] = 0.0f;
                        for (int k = 0; k < 4; k++) {
                                result[i][j] += a[i][k] * b[k][j];
                        }
                }
        }
}

int spriteInitialize(Sprite *sprite,
                     const char *tag,
                     ShaderProgram *shader,
                     Texture2D *texture) {
        sprite->tag = tag;
        sprite->shader = shader;
        sprite->texture = texture;

        sprite->height = 10;
        sprite->width = 10;
        sprite->X = 0;
        sprite->Y = 0;
        memcpy(sprite->color, PALETTE.transparent, sizeof(vec4));

        GLuint VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_VERTICES), SPRITE_VERTICES, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SPRITE_INDICES), SPRITE_INDICES, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        sprite->VBO = VBO;
        sprite->VAO = VAO;
        sprite->EBO = EBO;
        spriteApplyModel(sprite);

        return EXIT_SUCCESS;
}

int spriteRender(Sprite *sprite, Callback callback) {
        glActiveTexture(GL_TEXTURE0);
        textureBind(sprite->texture);

        shaderProgramUse(sprite->shader);


        if (callback != NULL) {
                callback(sprite);
        }
        spriteApplyModel(sprite);
        shaderSetMat4(sprite->shader, "uMVP", &sprite->MVP);
        shaderSetVec4f(sprite->shader, "uColor", sprite->color);
        shaderSetInt(sprite->shader, "uTexture", 0);

        glBindVertexArray(sprite->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

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
        //free(sprite);
        sprite = NULL;

        return EXIT_SUCCESS;
}

int spriteApplyModel(Sprite *sprite) {
        mat4 model, view, projection, MVP, scale, translate, rotate;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(projection);
        glm_mat4_identity(scale);
        glm_mat4_identity(translate);
        glm_mat4_identity(rotate);


        scale[0][0] = sprite->width;
        scale[1][1] = sprite->height;

        translate[0][3] = sprite->X;
        translate[1][3] = sprite->Y;

        mat4 tmp;
        mat4_mul(rotate, scale, tmp);
        mat4_mul(translate, tmp, model);

        float Z_FAR = 1;
        float Z_NEAR = -1;

        projection[0][0] = 2 / (VIEWPORT_WIDTH - VIEWPORT_ORIGIN);

        projection[1][1] = 2 / (VIEWPORT_HEIGHT - VIEWPORT_ORIGIN);

        projection[2][2] = 2 / (Z_FAR - Z_NEAR);
        projection[0][3] = - (VIEWPORT_WIDTH + VIEWPORT_ORIGIN) / (VIEWPORT_WIDTH - VIEWPORT_ORIGIN);
        projection[1][3] = - (VIEWPORT_HEIGHT + VIEWPORT_ORIGIN) / (VIEWPORT_HEIGHT - VIEWPORT_ORIGIN);
        projection[2][3] = - (Z_FAR + Z_NEAR) / (Z_FAR - Z_NEAR);


        mat4_mul(projection, model, MVP);
        glm_mat4_transpose(MVP);

        memcpy(sprite->MVP, MVP, sizeof(mat4));

        return EXIT_SUCCESS;
}

int spriteSetPosition(Sprite *p_sprite, const vec2 centeredPosition) {
        p_sprite->X = centeredPosition[0] - p_sprite->width / 2.0f;
        p_sprite->Y = centeredPosition[1] - p_sprite->height / 2.0f;

        return EXIT_SUCCESS;
}