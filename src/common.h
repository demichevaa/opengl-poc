#ifndef OPENGL_POC_COMMON_H
#define OPENGL_POC_COMMON_H

#include "viewport.h"

typedef void (*Callback)(void *);
int clampToViewport(vec2 centerPosition, float width, float height);

struct Direction {
    vec2 Top;
    vec2 Bottom;
    vec2 Left;
    vec2 Right;
};

static const struct Direction DIRECTION = {
        .Top = {0.0f , 1.0f},
        .Bottom = {0.0f, -1.0f},
        .Left = {-1.0f, 0.0f},
        .Right = {0.0f, 1.0f}
};


#endif //OPENGL_POC_COMMON_H
