#ifndef OPENGL_POC_SRC_TEXTURE_H_
#define OPENGL_POC_SRC_TEXTURE_H_

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

//#include "window.h"
#include "stb_image.h"
#include "render.h"
#include "debug.h"


typedef struct Texture2D {
        unsigned int id;
        GLenum format;
        const char *source;
        int width;
        int height;
} Texture2D;

int textureInitialize(Texture2D *texture, int width, int height, const unsigned char *data);
int textureBind(Texture2D *texture);

#endif //OPENGL_POC_SRC_TEXTURE_H_
