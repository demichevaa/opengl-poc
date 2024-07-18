#ifndef OPENGL_POC_BALL_H
#define OPENGL_POC_BALL_H

#include "sprite.h"
#include "assets.h"
#include "common.h"
#include "block.h"
#include "platform.h"


struct Ball {
    size_t id;
    float radius;
    vec2 direction;
    float speed;
    struct Sprite sprite;
    vec2 position;
    int damage;
    bool has_collision;
};

struct Ball ball_create();
int ball_render(struct Ball *p_ball, float time_delta);
int ball_update(struct Ball *p_ball, float time_delta);
int ball_on_hit_block(struct Ball *p_ball, struct Block *p_block);
int ball_on_hit_platform(struct Ball *p_ball, struct Platform *p_platform);
int ball_on_hit_wall(struct Ball *p_ball);

int ball_log(struct Ball *p_ball);

#endif //OPENGL_POC_BALL_H
