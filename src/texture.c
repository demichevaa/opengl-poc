#include "texture.h"

int textureInitialize(Texture2D *texture, int width, int height, const unsigned char *data) {
        if (data == NULL) {
                fprintf(stderr, "[TEXTURE:INITIALIZE] -> No data provided\n");
                exit(EXIT_FAILURE);
        }

        glGenTextures(1, &texture->id);

        texture->width = width;
        texture->height = height;

        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        printf("[TEXTURE:INITIALIZE] -> Texture %d created\n", texture->id);

        return EXIT_SUCCESS;
}

int textureBind(Texture2D *texture) {
        glBindTexture(GL_TEXTURE_2D, texture->id);
        return EXIT_SUCCESS;
}
