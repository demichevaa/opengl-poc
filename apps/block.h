#ifndef OPENGL_POC_APPS_BLOCK_H_
#define OPENGL_POC_APPS_BLOCK_H_

#include "sprite.h"
#include "assets.h"

typedef struct Block {
        Sprite sprite;
        int value;
} Block;

Block blockCreateSimple(float width, float height, float X, float Y);


#endif //OPENGL_POC_APPS_BLOCK_H_
