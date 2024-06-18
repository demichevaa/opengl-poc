#include "sprite.h"


float SPRITE_VERTICES[] = {
    -0.5f, -0.5f, 0.0f,        0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,         1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,         0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,          1.0f, 1.0f,
};
unsigned int SPRITE_INDICES[] = {
    0, 1, 2,
    2, 1, 3,
};


const char *UNIFORM_MODEL = "model";
const char *UNIFORM_COLOR = "spriteColor";


int spriteInitialize(Sprite *sprite,
                     const ShaderProgram *shader,
                     Texture2D *texture) {
        sprite->shader = shader;
        sprite->texture = texture;

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &sprite->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(sprite->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_VERTICES), SPRITE_VERTICES, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SPRITE_INDICES), SPRITE_INDICES, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        shaderProgramUse(sprite->shader);

        shaderSetInt(sprite->shader, "texture1", 0);


        return EXIT_SUCCESS;
}

int spriteRender(const Sprite *sprite,
                 vec2 position,
                 vec2 size,
                 float rotate_angle,
                 vec3 color) {

        printf("Render-in. program_id: %d, VAO: %d\n", sprite->shader->id, sprite->VAO);
        //glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        textureBind(sprite->texture);

        shaderProgramUse(sprite->shader);
        //glUseProgram(sprite->shader->id);

        glBindVertexArray(sprite->VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        printf("Render-out. program_id: %d, VAO: %d\n", sprite->shader->id, sprite->VAO);


        return EXIT_SUCCESS;
}



//       shaderProgramUse(sprite->shader);
//        mat4 model;
//        glm_mat4_identity(model);
//        glm_translate(model, position);
//        vec3 center = {0.5f * size[0], 0.5f * size[1], 0.0f};
//        glm_translate(model, center);
//        vec3 rotationAxis = {0.0f, 0.0f, 1.0f};
//        glm_rotate(model, glm_rad(rotate_angle), rotationAxis);
//        vec3 negativeOrigin = {-0.5f * size[0], -0.5f * size[1], 0.0f};
//
//        glm_translate(model, negativeOrigin);
//        vec3 scaleVec = {size[0], size[1], 1.0f};
//        glm_scale(model, scaleVec);

//        shaderSetMat4(sprite->shader, UNIFORM_MODEL, &model);
//        shaderSetVec3f(sprite->shader, UNIFORM_COLOR, (vec3 *)color);
