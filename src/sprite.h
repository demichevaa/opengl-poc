#ifndef OPENGL_POC_SRC_SPRITE_H_
#define OPENGL_POC_SRC_SPRITE_H_

#include "cglm/cglm.h"

#include "shader.h"
#include "texture.h"


typedef struct Sprite {
        int id;
        const ShaderProgram *shader;
        Texture2D *texture;
        unsigned int VAO;
} Sprite;


int spriteInitialize(Sprite *sprite, const ShaderProgram *shader, Texture2D *texture);
int spriteRender(const Sprite *sprite,
                 vec2 position,
                 vec2 size,
                 float rotate,
                 vec3 color);

#endif //OPENGL_POC_SRC_SPRITE_H_
