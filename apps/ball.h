#ifndef OPENGL_POC_BALL_H
#define OPENGL_POC_BALL_H

#include "sprite.h"
#include "assets.h"
#include "common.h"

struct Ball {
    float radius;
    vec2 velocity;
    vec2 direction;
    float speed;
    Sprite sprite;
    vec2 position;
};

struct Ball ballCreate();
int ballRender(struct Ball *p_ball, float timeDelta);

#endif //OPENGL_POC_BALL_H
