#include "block.h"

Block blockCreateSimple(float width, float height, float X, float Y) {
        Block block;
        Sprite sprite;

        spriteCreateFromAssets(&sprite, "simple_block", "textures/block.png");

        sprite.width = width;
        sprite.height = height;
        block.sprite = sprite;
        block.sprite.X = X;
        block.sprite.Y = Y;

        return block;
}
