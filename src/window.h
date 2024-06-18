#ifndef OPENGL_POC_SRC_WINDOW_H_
#define OPENGL_POC_SRC_WINDOW_H_

#include <stdio.h>
#include "render.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow *create_window(char *title, int width, int height);

#endif //OPENGL_POC_SRC_WINDOW_H_
