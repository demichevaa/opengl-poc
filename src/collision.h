#ifndef OPENGL_POC_COLLISION_H
#define OPENGL_POC_COLLISION_H

#include "sprite.h"


bool collision_check_ABBB(struct Sprite *p_a, struct Sprite *p_b);
bool collision_check_x(struct Sprite *p_a, float min_x, float max_x);
bool collision_check_circle_ABBB(struct Sprite *p_circle, struct Sprite *p_rectangle);
bool collision_has_overlap_x(struct Sprite *p_a, struct Sprite *p_b);

#endif //OPENGL_POC_COLLISION_H
