#ifndef OPENGL_POC_APPS_BLOCK_H_
#define OPENGL_POC_APPS_BLOCK_H_

#include "sprite.h"
#include "assets.h"
#include "ball.h"

typedef struct Block {
        struct Sprite sprite;
        int health;
        bool is_dead;
} Block;

enum BlockType {
    WALL = -1,
    HP_5 = 5,
    HP_4 = 4,
    HP_3 = 3,
    HP_2 = 2,
    HP_1 = 1
};

Block block_create(float width, float height, float X, float Y, enum BlockType type,
                          unsigned int hp, bool is_destroyable);
int block_on_hit(Block *p_block, struct Ball *p_ball);
int block_render(Block *p_block);

#endif //OPENGL_POC_APPS_BLOCK_H_
