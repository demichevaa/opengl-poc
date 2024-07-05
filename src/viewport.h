#ifndef OPENGL_POC_SRC_VIEWPORT_H_
#define OPENGL_POC_SRC_VIEWPORT_H_

#include "window.h"
#include <cglm/cglm.h>

extern const float GAME_WIDTH;
extern const float GAME_HEIGHT;
extern const float GAME_ASPECT;

int viewportSetOrthogonalProjection(mat4 *p_projection);


#endif //OPENGL_POC_SRC_VIEWPORT_H_
