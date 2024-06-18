#include "debug.h"

const int ENABLE_DEBUG = 1;

void debug() {
        unsigned int error;
        if ((error = glGetError()) != GL_NO_ERROR) {
                fprintf(stderr, "[DEBUG:UNHANDLED_GL_ERROR] -> %d\n", error);
        }
}

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam) {
        printf("test");
}