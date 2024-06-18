#ifndef OPENGL_POC_SRC_DEBUG_H_
#define OPENGL_POC_SRC_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>

#include "render.h"

void debug();
void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam);
extern const int ENABLE_DEBUG;

#endif //OPENGL_POC_SRC_DEBUG_H_
