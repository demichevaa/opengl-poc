#ifndef OPENGL_POC_SRC_SPRITE_H_
#define OPENGL_POC_SRC_SPRITE_H_

#include "cglm/cglm.h"
#include <limits.h>

#include "shader.h"
#include "texture.h"

typedef struct Sprite {
        const char *tag;
        ShaderProgram *shader;
        Texture2D *texture;
        vec2 position;
        float rotation;
        vec3 color;

        mat3 scale;
        mat3 model;
        mat3 projection;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

} Sprite;


int spriteInitialize(Sprite *sprite, const char *tag, ShaderProgram *shader, Texture2D *texture);
int spriteRender(Sprite *sprite);
int spriteRelease(Sprite *sprite);
int spriteSetPosition(Sprite *sprite, const vec2 position);
int spriteSetScale(Sprite *sprite, vec2 scale);
int spriteSetRotationAngle(Sprite *sprite, float angle);
int spriteApplyModel(Sprite *sprite);



#endif //OPENGL_POC_SRC_SPRITE_H_
