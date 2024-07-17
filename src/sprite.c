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

int sprite_initialize(
        struct Sprite *p_sprite,
        struct ShaderProgram *p_shader,
        struct Texture2D *p_texture
) {
        p_sprite->p_shader = p_shader;
        p_sprite->p_texture = p_texture;

        p_sprite->height = 10;
        p_sprite->width = 10;
        p_sprite->X = 0;
        p_sprite->Y = 0;
        memcpy(p_sprite->color, PALETTE.transparent, sizeof(vec4));

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

        p_sprite->VBO = VBO;
        p_sprite->VAO = VAO;
        p_sprite->EBO = EBO;
        sprite_apply_model(p_sprite);

        return EXIT_SUCCESS;
}

int sprite_render(struct Sprite *p_sprite, Callback callback) {
        glActiveTexture(GL_TEXTURE0);
        texture_bind(p_sprite->p_texture);

        shader_use(p_sprite->p_shader);


        if (callback != NULL) {
                callback(p_sprite);
        }
        sprite_apply_model(p_sprite);
        shader_set_mat4(p_sprite->p_shader, "uMVP", &p_sprite->MVP);
        shaderSetVec4f(p_sprite->p_shader, "uColor", p_sprite->color);
        shaderSetInt(p_sprite->p_shader, "uTexture", 0);

        glBindVertexArray(p_sprite->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        return EXIT_SUCCESS;
}

int sprite_free(struct Sprite *p_sprite) {
        free(p_sprite->p_shader);
        free(p_sprite->p_texture);

        glDeleteVertexArrays(1, &p_sprite->VAO);
        glDeleteBuffers(1, &p_sprite->EBO);
        glDeleteBuffers(1, &p_sprite->VBO);

        p_sprite->p_shader = NULL;
        p_sprite->p_texture = NULL;
        p_sprite->VAO = INT_MAX;
        p_sprite->EBO = INT_MAX;
        p_sprite->VBO = INT_MAX;

        printf("[SPRITE:FREE] -> Sprite destroyed at (%.2fx%.2f)\n", p_sprite->X, p_sprite->Y);
        p_sprite = NULL;

        return EXIT_SUCCESS;
}

int sprite_apply_model(struct Sprite *p_sprite) {
        mat4 model, view, projection, MVP, scale, translate, rotate;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(projection);
        glm_mat4_identity(scale);
        glm_mat4_identity(translate);
        glm_mat4_identity(rotate);


        scale[0][0] = p_sprite->width;
        scale[1][1] = p_sprite->height;

        translate[0][3] = p_sprite->X;
        translate[1][3] = p_sprite->Y;

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

        memcpy(p_sprite->MVP, MVP, sizeof(mat4));

        return EXIT_SUCCESS;
}

int sprite_set_position(struct Sprite *p_sprite, const vec2 centeredPosition) {
        p_sprite->X = centeredPosition[0] - p_sprite->width / 2.0f;
        p_sprite->Y = centeredPosition[1] - p_sprite->height / 2.0f;

        return EXIT_SUCCESS;
}