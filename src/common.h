#ifndef OPENGL_POC_COMMON_H
#define OPENGL_POC_COMMON_H

#include "viewport.h"

typedef int (*Callback)(void *);
int clamp_to_viewport(vec2 centerPosition, float width, float height);
int for_each(void *data, size_t dim_1, size_t dim_2, size_t elem_size, Callback callback);

struct Direction {
    vec2 Top;
    vec2 Bottom;
    vec2 Left;
    vec2 Right;
};

static struct Direction DIRECTION = {
        .Top = {0.0f , 1.0f},
        .Bottom = {0.0f, -1.0f},
        .Left = {-1.0f, 0.0f},
        .Right = {0.0f, 1.0f}
};

int direction_invert(vec2 direction);



#endif //OPENGL_POC_COMMON_H
