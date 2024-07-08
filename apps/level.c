#include "level.h"

float calcColMargin(int colsCount, float colSize, float containerSize) {
        return  (containerSize - ((float)colsCount * colSize)) / 2.0f;
}


int levelInitialize(Level *level, int rowsCount, int colsCount, int data[rowsCount][colsCount]) {
        level->rowsCount = rowsCount;
        level->columnsCount = colsCount;

        float blockWidth = 10.0f;
        float blockHeight = 5.0f;

        float blockPadding = 0.1f;
        float blockWidthAligned = blockWidth + blockPadding;
        float blockHeightAligned = blockHeight + blockPadding;

        float colMargin = calcColMargin(colsCount, blockWidthAligned, VIEWPORT_WIDTH);
        float rowMargin = 2.0f;

        float xOrigin = VIEWPORT_ORIGIN + colMargin;
        float x = xOrigin;
        float y = VIEWPORT_HEIGHT - rowMargin;


        level->blocks = malloc(rowsCount * sizeof(Block *));
        for (int i = 0; i < rowsCount; i++) {
                y -= blockHeightAligned;
                level->blocks[i] = malloc(colsCount * sizeof(Block));
                for (int j = 0; j < colsCount; j++) {
                        Block block = blockCreateSimple(blockWidth, blockHeight, x, y);
                        level->blocks[i][j] = block;
                        x += blockWidthAligned;
                }
                x = xOrigin;
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
