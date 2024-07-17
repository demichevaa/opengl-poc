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

int vec2_invert(vec2 v, enum Axis axis) {
        switch (axis) {
                case X_AXIS:
                        v[0] *= -1;
                        break;
                case Y_AXIS:
                        v[1] *= -1;
                        break;
                case X_Y_AXES:
                        glm_vec2_scale(v, -1.0f, v);
                        break;
                default:
                        return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
//        if (v[1] > v[0]) {
//                v[0] *= -1;
//                return EXIT_SUCCESS;
//        }
//        v[1] *= -1;
//        return EXIT_SUCCESS;
}

