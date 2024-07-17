#include "block.h"
#include "ball.h"


int assignDecodedColor(vec4 color, enum BlockType colorCode) {
        switch (colorCode) {
                case WALL: {
                        glm_vec4_copy((float *) &PALETTE.cabSav, color);
                        break;
                }
                case HP_1: {
                        glm_vec4_copy((float *) &PALETTE.goldTips, color);
                        break;
                }
                case HP_2: {
                        glm_vec4_copy((float *) &PALETTE.sandyBrown, color);
                        break;
                }
                case HP_3: {
                        glm_vec4_copy((float *) &PALETTE.outrageousOrange, color);
                        break;
                }
                case HP_4: {
                        glm_vec4_copy((float *) &PALETTE.fireBrick, color);
                        break;
                }
                case HP_5: {
                        glm_vec4_copy((float *) &PALETTE.cherokee, color);
                        break;
                }
                default: {
                        fprintf(stderr, "[LEVEL:INITIALIZE] -> Unknown color code %d\n", colorCode);
                        glm_vec4_copy((float *) &PALETTE.transparent, color);
                        return EXIT_FAILURE;
                }
        }

        return EXIT_SUCCESS;
}


Block blockCreateSimple(
        float width,
        float height,
        float X,
        float Y,
        enum BlockType type,
        unsigned int hp,
        bool isDestroyable
) {
        ShaderProgram *program = malloc(sizeof(ShaderProgram));
        shaderCreateFromAssets(program, "shaders/block.vertex.glsl", "shaders/block.fragment.glsl", NULL);

        Texture2D *texture = malloc(sizeof(Texture2D));
        if (type == WALL) {
                textureCreateFromAssets(texture,  "textures/block_solid.png");
        }
        else {
                textureCreateFromAssets(texture,  "textures/block.png");
        }

        Block block;
        spriteInitialize(&block.sprite, "block", program, texture);

        //Sprite sprite;
        block.sprite.width = width;
        block.sprite.height = height;
        //block.sprite = sprite;
        block.sprite.X = X;
        block.sprite.Y = Y;
        block.is_dead = false;

        assignDecodedColor(block.sprite.color, type);

        if (isDestroyable) {
                block.health = 0;
        }

        return block;
}

int blockRenderUniformCallback(Sprite *sprite) {
        float aspectRatio = sprite->width / sprite->height;
        shaderSetFloat(sprite->shader, "uTextureAspectRatio", aspectRatio);

        return EXIT_SUCCESS;
}

int blockRender(Block *p_block) {
        if (p_block->is_dead) {
                return EXIT_SUCCESS;
        }

        spriteRender(&p_block->sprite, (Callback) blockRenderUniformCallback);
        return EXIT_SUCCESS;
}

int block_on_hit(Block *p_block, struct Ball *p_ball) {
        p_block->health -= p_ball->damage;
        direction_invert(p_ball->direction);

        printf("[BLOCK:HIT] -> Hit received. Hp: %i is_dead %i\n", p_block->health, p_block->is_dead);
        if (p_block->health <= 0) {
                p_block->is_dead = true;
                printf("[BLOCK:DESTROYED] -> Destroying block. Hp: %i is_dead %i\n", p_block->health, p_block->is_dead);

                //spriteRelease(&p_block->sprite);
        }

        return EXIT_SUCCESS;
}
