#include "common.h"

int clampToViewport(vec2 centerPosition, float width, float height) {
        float xDisplacement = width / 2.0f;
        float yDisplacement = height / 2.0f;
        float left = centerPosition[0] - xDisplacement;
        float right = centerPosition[0] + xDisplacement;
        float top = centerPosition[1] + yDisplacement;
        float bottom = centerPosition[1] - yDisplacement;

        if (right >= VIEWPORT_WIDTH) {
                centerPosition[0] = VIEWPORT_WIDTH - xDisplacement;
        }
        else if (left <= VIEWPORT_ORIGIN) {
                centerPosition[0] = VIEWPORT_ORIGIN + xDisplacement;
        }
        else if (top >= VIEWPORT_HEIGHT) {
                centerPosition[1] = VIEWPORT_HEIGHT - yDisplacement;
        }
        else if (bottom <= VIEWPORT_ORIGIN) {
                centerPosition[1] = VIEWPORT_ORIGIN + yDisplacement;
        }

        return EXIT_SUCCESS;
}

int direction_invert(vec2 direction){
        glm_vec2_scale(direction, -1.0f, direction);
}

int for_each(void *data, size_t dim_1, size_t dim_2, size_t elem_size, Callback callback) {
        bool has_callback = callback != NULL;
        bool has_dim_2 = dim_2 > 0;

        for (size_t i = 0; i < dim_1; i++) {
                if (has_callback && !has_dim_2) {
                        callback((char *)data + i * elem_size);
                        continue;
                }

                for (size_t j = 0; j < dim_2; j++) {
                        if (has_callback) {
                                callback((char *)data + (i * dim_2 + j) * elem_size);
                        }
                }
        }
        return EXIT_SUCCESS;
}