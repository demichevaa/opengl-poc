#include <stdlib.h>
#include "window.h"

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam);

GLFWwindow *create_window(char *title, int width, int height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);


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

        // debug
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, NULL);
        //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

        return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(-1, 0, width, height);
}


void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam)
{
        // Ignore non-significant error/warning codes
        //if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        fprintf(stderr, "---------------\n");
        fprintf(stderr, "Debug message (%d): %s\n", id, message);

        switch (source)
        {
                case GL_DEBUG_SOURCE_API:             fprintf(stderr, "Source: API"); break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   fprintf(stderr, "Source: Window System"); break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: fprintf(stderr, "Source: Shader Compiler"); break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     fprintf(stderr, "Source: Third Party"); break;
                case GL_DEBUG_SOURCE_APPLICATION:     fprintf(stderr, "Source: Application"); break;
                case GL_DEBUG_SOURCE_OTHER:           fprintf(stderr, "Source: Other"); break;
        } fprintf(stderr, "\n");

        switch (type)
        {
                case GL_DEBUG_TYPE_ERROR:               fprintf(stderr, "Type: Error"); break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: fprintf(stderr, "Type: Deprecated Behaviour"); break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  fprintf(stderr, "Type: Undefined Behaviour"); break;
                case GL_DEBUG_TYPE_PORTABILITY:         fprintf(stderr, "Type: Portability"); break;
                case GL_DEBUG_TYPE_PERFORMANCE:         fprintf(stderr, "Type: Performance"); break;
                case GL_DEBUG_TYPE_MARKER:              fprintf(stderr, "Type: Marker"); break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          fprintf(stderr, "Type: Push Group"); break;
                case GL_DEBUG_TYPE_POP_GROUP:           fprintf(stderr, "Type: Pop Group"); break;
                case GL_DEBUG_TYPE_OTHER:               fprintf(stderr, "Type: Other"); break;
        } fprintf(stderr, "\n");

        switch (severity)
        {
                case GL_DEBUG_SEVERITY_HIGH:         fprintf(stderr, "Severity: high"); break;
                case GL_DEBUG_SEVERITY_MEDIUM:       fprintf(stderr, "Severity: medium"); break;
                case GL_DEBUG_SEVERITY_LOW:          fprintf(stderr, "Severity: low"); break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: fprintf(stderr, "Severity: notification"); break;
        } fprintf(stderr, "\n");
        fprintf(stderr, "\n");

        exit(EXIT_FAILURE);
}
