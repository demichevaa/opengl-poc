#ifndef OPENGL_POC_SRC_SPRITE_H_
#define OPENGL_POC_SRC_SPRITE_H_

#include "cglm/cglm.h"
#include <limits.h>
#include <memory.h>


#include "shader.h"
#include "texture.h"
#include "viewport.h"
#include "palette.h"
#include "common.h"


struct Sprite {
        struct ShaderProgram *p_shader;
        struct Texture2D *p_texture;

        float X;
        float Y;
        float width;
        float height;
        vec4 color;

        mat4 MVP;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

};

typedef int (*UniformCallback)(struct Sprite *, void *);

int sprite_initialize(struct Sprite *p_sprite, struct ShaderProgram *p_shader, struct Texture2D *p_texture);
int sprite_render(struct Sprite *p_sprite, void *context, UniformCallback callback);
int sprite_free(struct Sprite *p_sprite);
int sprite_set_scale(struct Sprite *p_sprite, vec2 scale);
int sprite_set_rotation_angle(struct Sprite *p_sprite, float angle);
int sprite_set_position(struct Sprite *p_sprite, const vec2 centered_position);
int sprite_apply_model(struct Sprite *p_sprite);



#endif //OPENGL_POC_SRC_SPRITE_H_
