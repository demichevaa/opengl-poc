#ifndef OPENGL_POC_COMMON_H
#define OPENGL_POC_COMMON_H

#include "viewport.h"

#define SQRT2_INV (1.0f / 1.41421356237f)

typedef int (*Callback)(void *);
int clamp_to_viewport(vec2 centerPosition, float width, float height);
int for_each(void *data, size_t dim_1, size_t dim_2, size_t elem_size, Callback callback);

struct Direction {
    vec2 N;
    vec2 S;
    vec2 W;
    vec2 E;
    vec2 NE;
    vec2 NW;
    vec2 SE;
    vec2 SW;
};


enum Axis {
    X_AXIS,
    Y_AXIS,
    X_Y_AXES
};

static struct Direction DIRECTION = {
        .N = {0.0f, 1.0f},
        .S = {0.0f, -1.0f},
        .W = {-1.0f, 0.0f},
        .E = {1.0f, 0.0f},
        .NE = {SQRT2_INV, SQRT2_INV},
        .NW = {-SQRT2_INV, SQRT2_INV},
        .SE = {SQRT2_INV, -SQRT2_INV},
        .SW = {-SQRT2_INV, -SQRT2_INV}
};
int vec2_invert(vec2 v, enum Axis axis);

#endif //OPENGL_POC_COMMON_H
