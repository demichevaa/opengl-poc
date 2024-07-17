#include "common.h"

int clamp_to_viewport(vec2 centerPosition, float width, float height) {
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

