#ifndef OPENGL_POC_APPS_BLOCK_H_
#define OPENGL_POC_APPS_BLOCK_H_

#include "sprite.h"
#include "assets.h"

typedef struct Block {
        Sprite sprite;
        unsigned int health;
        bool isDestroyable;
} Block;

enum BlockType {
    WALL = -1,
    HP_5 = 5,
    HP_4 = 4,
    HP_3 = 3,
    HP_2 = 2,
    HP_1 = 1
};

Block blockCreateSimple(float width, float height, float X, float Y, enum BlockType type,
                        unsigned int hp, bool isDestroyable);
int blockRender(Block *p_block);

#endif //OPENGL_POC_APPS_BLOCK_H_
