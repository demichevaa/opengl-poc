#ifndef OPENGL_POC_APPS_LEVEL_H_
#define OPENGL_POC_APPS_LEVEL_H_

#include "block.h"
#include "assets.h"
#include "viewport.h"


struct Level {
        size_t id;
        struct Block **blocks;
        int rows_count;
        int columns_count;
};

int level_initialize(struct Level *p_level, int rows_count, int cols_count, int data[rows_count][cols_count]);
int level_render(struct Level *p_level);

#endif //OPENGL_POC_APPS_LEVEL_H_
