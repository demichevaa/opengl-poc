#ifndef OPENGL_POC_SRC_VIEWPORT_H_
#define OPENGL_POC_SRC_VIEWPORT_H_

#include "window.h"
#include <cglm/cglm.h>

extern const float VIEWPORT_WIDTH;
extern const float VIEWPORT_HEIGHT;
extern const float VIEWPORT_ORIGIN;
extern const float VIEWPORT_ASPECT_RATIO;

int viewportSetOrthogonalProjection(mat4 *p_projection);


#endif //OPENGL_POC_SRC_VIEWPORT_H_
