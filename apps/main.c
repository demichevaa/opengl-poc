#include "window.h"
#include "assets.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

void processInput(GLFWwindow *window);

int main() {
        char * level_1 = assetGetContent("levels/level_1.lvl");
        printf(level_1);

        GLFWwindow *window = create_window("opengl-app", SCREEN_WIDTH, SCREEN_HEIGHT);

        ShaderProgram program;
        shaderCreateFromAssets(&program, "shaders/test.vertex.glsl", "shaders/test.fragment.glsl", NULL);

        Texture2D texture;
        textureCreateFromAssets(&texture, "textures/debug.png");

//        Sprite sprite;
//        spriteCreateFromAssets(&sprite, "textures/debug.png");

        Sprite sprite;
        spriteInitialize(&sprite, &program, &texture);


        int i = 0;
        while (!glfwWindowShouldClose(window)) {
                printf("Loop-%d out: program_id: %d\n" , i, sprite.shader->id);

                processInput(window);

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                spriteRender(&sprite, NULL, NULL, 0.0f, NULL);
                printf("Loop-%d after render: program_id: %d\n" , i, sprite.shader->id);
                glfwSwapBuffers(window);
                printf("Loop-%d after glfwSwapBuffers: program_id: %d\n\n\n" , i, sprite.shader->id);

                glfwPollEvents();
                printf("Loop-%d out: program_id: %d\n\n\n" , i, sprite.shader->id);
                i++;

        }

//        glDeleteVertexArrays(1, &VAO);
//        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
        glfwTerminate();

        return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, 1);
}
