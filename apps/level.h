#ifndef OPENGL_POC_APPS_LEVEL_H_
#define OPENGL_POC_APPS_LEVEL_H_

#include "block.h"
#include "assets.h"

typedef struct Level {
        Block ** blocks;
        int rowsCount;
        int columnsCount;

} Level;

int levelInitialize(Level *level, int rowsCount, int colsCount, int data[rowsCount][colsCount]);
int levelRender(Level *pLevel);

#endif //OPENGL_POC_APPS_LEVEL_H_
