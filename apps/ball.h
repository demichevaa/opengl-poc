#ifndef OPENGL_POC_BALL_H
#define OPENGL_POC_BALL_H

#include "sprite.h"
#include "assets.h"
#include "common.h"
#include "block.h"

struct Ball {
    float radius;
    vec2 direction;
    float speed;
    struct Sprite sprite;
    vec2 position;
    int damage;
};

struct Ball ball_create();
int ball_render(struct Ball *p_ball, float time_delta);
int ball_update(struct Ball *p_ball, float time_delta);
#endif //OPENGL_POC_BALL_H
