#ifndef OPENGL_POC_PLATFORM_H
#define OPENGL_POC_PLATFORM_H

#include "sprite.h"

struct Platform {
    Sprite sprite;
    float x;
    float velocity;
    float size;
};

struct Platform platformCreate();
int platformRender(struct Platform *p_platform, float timeDelta);
int platformHandleInput(struct Platform *p_platform, int key, int action);

#endif //OPENGL_POC_PLATFORM_H
