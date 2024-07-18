#ifndef OPENGL_POC_PLATFORM_H
#define OPENGL_POC_PLATFORM_H

#include "sprite.h"
#include "input.h"
#include "assets.h"
#include "common.h"


struct Platform {
    size_t id;
    struct Sprite sprite;
    vec2 position;
    float velocity;
    float size;
    float edge_hit_box_ratio;

    bool has_active_collision;
};

struct Platform platform_create();
int platform_render(struct Platform *p_platform, float time_delta);
int platform_handle_input(struct Platform *p_platform, enum Actions action, float time_delta);
int platform_log(struct Platform *p_platform);

#endif //OPENGL_POC_PLATFORM_H
