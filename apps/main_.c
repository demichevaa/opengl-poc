#include <stdio.h>

#include "window.h"
#include "assets.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void processInput(GLFWwindow *window);

int get_texture(const char *assetRelativePath) {
        char file_name[1024];
        sprintf(file_name, "%s%s", "./assets/", assetRelativePath);

        int width, height, nrChannels;
        unsigned char
            *data = stbi_load(file_name, &width, &height, &nrChannels, 0);

        unsigned int texture;

        glGenTextures(1, &texture);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glBindTexture(GL_TEXTURE_2D, texture);

        stbi_image_free(data);

        return texture;
}

int main() {
        GLFWwindow
            *window = create_window("opengl-app", SCREEN_WIDTH, SCREEN_HEIGHT);
        printf("Yep!\n");

        int texture = get_texture("textures/block.png");
        printf("Texture: %d\n", texture);

        ShaderProgram program;
        shaderCreateFromAssets(&program,
                               "shaders/test.vertex.glsl",
                               "shaders/test.fragment.glsl",
                               NULL);
        shaderProgramUse(&program);
        shaderSetInt(&program, "texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        const float vertices[] = {
            // pos      // tex
            -0.5f,  0.5f, 0.0f, 1.0f, // top-left
            0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left

            -0.5f,  0.5f, 0.0f, 1.0f, // top-left
            0.5f,  0.5f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, 1.0f, 0.0f  // bottom-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glBindVertexArray(VAO);
                shaderProgramUse(&program);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);


                glfwSwapBuffers(window);
                glfwPollEvents();
        }
        return 0;
}

void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, 1);
}
