#ifndef OPENGL_POC_PLATFORM_H
#define OPENGL_POC_PLATFORM_H

#include "sprite.h"
#include "input.h"
#include "assets.h"


struct Platform {
    struct Sprite sprite;
    vec2 position;
    float velocity;
    float size;
};

struct Platform platform_create();
int platform_render(struct Platform *p_platform, float time_delta);
int platform_handle_input(struct Platform *p_platform, enum Actions action, float time_delta);

#endif //OPENGL_POC_PLATFORM_H
