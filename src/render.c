#include <memory.h>
#include "cglm/cglm.h"
#include "texture.h"
#include "shader.h"
#include "viewport.h"

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

struct Render {
    ShaderProgram *shaderProgram;
    Texture2D *texture;

    mat4 MVP;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    float width;
    float height;
    float x;
    float y;
};

int renderApplyModel(
        struct Render *p_render
) {
        mat4 model, view, projection, MVP, scale, translate, rotate;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(projection);
        glm_mat4_identity(scale);
        glm_mat4_identity(translate);
        glm_mat4_identity(rotate);


        scale[0][0] = p_render->width;
        scale[1][1] = p_render->height;

        translate[0][3] = p_render->x;
        translate[1][3] = p_render->y;

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

        memcpy(p_render->MVP, MVP, sizeof(mat4));

        return EXIT_SUCCESS;
}


int renderInitialize(struct Render *p_render, ShaderProgram *p_shaderProgram, Texture2D *p_texture) {
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

        p_render->VBO = VBO;
        p_render->VAO = VAO;
        p_render->EBO = EBO;

        return EXIT_SUCCESS;
}
//
//int renderDraw(struct Render *p_render) {
//        renderApplyModel(p_render);
//
//        glActiveTexture(GL_TEXTURE0);
//        textureBind(p_render->texture);
//
//        shaderProgramUse(p_render->shaderProgram);
//        shaderSetMat4(p_render->shaderProgram, "MVP", &sprite->MVP);
//        shaderSetVec4f(sprite->shader, "spriteColor", sprite->color);
//        float aspectRatio = sprite->width / sprite->height;
//        shaderSetFloat(sprite->shader, "textureAspectRatio", aspectRatio);
//
//        glBindVertexArray(sprite->VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//
//        return EXIT_SUCCESS;
//}