#include "level.h"

int levelInitialize(Level *level, int rowsCount, int colsCount, int data[rowsCount][colsCount]) {

        level->blocks = malloc(rowsCount * sizeof(Block *));
        level->rowsCount = rowsCount;
        level->columnsCount = colsCount;

        for (int i = 0; i < rowsCount; i++) {
                level->blocks[i] = malloc(colsCount * sizeof(Block));
                for (int j = 0; j < colsCount; j++) {
                        Sprite blockSprite;
                        Block block;

                        spriteCreateFromAssets(&blockSprite, "simple_block", "textures/block.png");

                        block.sprite = blockSprite;
                        block.value = data[i][j];
                        level->blocks[i][j] = block;
                }
        }
        return EXIT_SUCCESS;
}

int levelRender(Level *pLevel) {
        for (int i = 0; i < pLevel->rowsCount; ++i) {
                for (int j = 0; j < pLevel->columnsCount; ++j) {
                        spriteRender(&pLevel->blocks[i][j].sprite);
                }
        }

        return EXIT_SUCCESS;
}
