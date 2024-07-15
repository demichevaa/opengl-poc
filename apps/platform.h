#ifndef OPENGL_POC_PLATFORM_H
#define OPENGL_POC_PLATFORM_H

#include "sprite.h"
#include "input.h"
#include "assets.h"


struct Platform {
    Sprite sprite;
    float x;
    float y;
    float velocity;
    float size;
};

struct Platform platformCreate();
int platformRender(struct Platform *p_platform, float timeDelta);
int platformHandleInput(struct Platform *p_platform, enum Actions action, float timeDelta);

#endif //OPENGL_POC_PLATFORM_H
