#include "window.h"

void tempDebugInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* createWindow(float width, float height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow((int)width, (int)height, "LearnOpenGL", NULL, NULL);
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glViewport(0, 0, (int) width, (int) height);

        glfwSetKeyCallback(window, inputCallback);


        return window;
}

GLFWwindow* windowInitialize(Window *p_window, char *title, float width, float height) {
        printf("[WINDOW:INITIALIZE] -> Creating glfw window (%dx%d): `%s` \n", (int)width, (int)height, title);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, ENABLE_DEBUG);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


        GLFWwindow *window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
        if (window == NULL) {
                fprintf(stderr, "Failed to create GLFW window");
                glfwTerminate();
                //return EXIT_FAILURE;
        }
        glfwMakeContextCurrent(window);
        //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initialize GLAD\n");
                glfwTerminate();
                //return EXIT_FAILURE;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0, 0, (int)width, (int)height);
        //glMatrixMode(GL_PROJECTION);


        if (ENABLE_DEBUG == 1) {
                printf("[WINDOW:INITIALIZE] -> OpenGL debug mode enabled\n");
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, NULL);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

        }

        p_window->width = width;
        p_window->height = height;
        p_window->glfw_window = window;


        //windowRegisterInputCallback(inputCallback);

        return window;
}

int windowRegisterInputCallback(Window *p_window) {
        glfwSetKeyCallback(p_window->glfw_window, tempDebugInputCallback);

        return EXIT_SUCCESS;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(-1, 0, width, height);
}

void tempDebugInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
}
