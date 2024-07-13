#include "window.h"
#include "game.h"

float WINDOW_WIDTH = 1366;
float WINDOW_HEIGHT = 768;

void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
        Game *p_game = (Game*)glfwGetWindowUserPointer(window);

        glfwGetTime();
        if (p_game != NULL) {
                gameHandleInput(p_game, key, action);
        }
}


int main() {
        GLFWwindow *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);


        Game game;
        gameInitialize(&game);

        glfwSetWindowUserPointer(window, &game);
        glfwSetKeyCallback(window, inputCallback);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                printf("%f\n", deltaTime);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                renderLoop(&game, deltaTime);
                glfwSwapBuffers(window);
        }

        return EXIT_SUCCESS;
}
