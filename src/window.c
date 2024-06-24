#include "window.h"

GLFWwindow *create_window(char *title, int width, int height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, ENABLE_DEBUG);


        GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL) {
                printf("Failed to create GLFW window");
                glfwTerminate();
                return NULL;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                printf("Failed to initialize GLAD\n");
                return NULL;
        }

        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glMatrixMode(GL_PROJECTION);

        if (ENABLE_DEBUG == 1) {
                printf("[WINDOW] -> Debug enabled.\n");
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, NULL);
                //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

        }

        return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(-1, 0, width, height);
}


