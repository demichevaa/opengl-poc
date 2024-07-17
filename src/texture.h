#ifndef OPENGL_POC_SRC_TEXTURE_H_
#define OPENGL_POC_SRC_TEXTURE_H_

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

//#include "window.h"
#include "stb_image.h"
#include "render.h"
#include "debug.h"


struct Texture2D {
        unsigned int id;
        GLenum format;
        const char *source;
        int width;
        int height;
};

int texture_initialize(struct Texture2D *p_texture, int width, int height, const unsigned char *str_data);
int texture_bind(struct Texture2D *p_texture);

#endif //OPENGL_POC_SRC_TEXTURE_H_
