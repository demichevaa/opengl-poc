#ifndef OPENGL_POC_APPS_BLOCK_H_
#define OPENGL_POC_APPS_BLOCK_H_

#include "sprite.h"
#include "assets.h"


struct Block {
        size_t id;
        struct Sprite sprite;
        int health;
        bool is_dead;
};

enum BlockType {
    WALL = -1,
    HP_5 = 5,
    HP_4 = 4,
    HP_3 = 3,
    HP_2 = 2,
    HP_1 = 1
};

struct Block block_create(float width, float height, float X, float Y, enum BlockType type,
                          unsigned int hp, bool is_destroyable);
int block_render(struct Block *p_block);

#endif //OPENGL_POC_APPS_BLOCK_H_
