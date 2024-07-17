#include "level.h"

float calc_col_margin(int cols_count, float col_size, float container_size) {
        return  (container_size - ((float)cols_count * col_size)) / 2.0f;
}

int level_initialize(struct Level *p_level, int rows_count, int cols_count, int data[rows_count][cols_count]) {
        printf("[LEVEL:INITIALIZE] -> Loading level (%d %d)\n", rows_count, cols_count);

        p_level->rows_count = rows_count;
        p_level->columns_count = cols_count;

        float block_width = 10.0f;
        float block_height = 3.0f;

        float block_padding = 0.15f;
        float block_width_aligned = block_width + block_padding;
        float block_height_aligned = block_height + block_padding;

        float col_margin = calc_col_margin(cols_count, block_width_aligned, VIEWPORT_WIDTH);
        float row_margin = 1.0f;

        float x_origin = VIEWPORT_ORIGIN + col_margin;
        float x = x_origin;
        float y = VIEWPORT_HEIGHT - row_margin;


        p_level->blocks = malloc(rows_count * sizeof(struct Block *));
        for (int i = 0; i < rows_count; i++) {
                y -= block_height_aligned;
                p_level->blocks[i] = malloc(cols_count * sizeof(struct Block));
                for (int j = 0; j < cols_count; j++) {
                        int s = data[i][j];
                        struct Block block = block_create(block_width, block_height, x, y, s, 5, true);

                        p_level->blocks[i][j] = block;
                        x += block_width_aligned;
                }
                x = x_origin;
        }

        return EXIT_SUCCESS;
}

int level_render(struct Level *p_level) {
        for (int i = 0; i < p_level->rows_count; ++i) {
                for (int j = 0; j < p_level->columns_count; ++j) {
                        block_render(&p_level->blocks[i][j]);
                }
        }

        return EXIT_SUCCESS;
}

