#ifndef OPENGL_POC_SRC_WINDOW_H_
#define OPENGL_POC_SRC_WINDOW_H_

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "render.h"
#include "screen.h"

typedef struct Window {
        float width;
        float height;
        GLFWwindow *glfw_window;
} Window;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int windowInitialize(Window *p_window, char *title, float width, float height);
int windowRegisterInputCallback(Window *p_window);


#endif //OPENGL_POC_SRC_WINDOW_H_
