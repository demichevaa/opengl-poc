#include "texture.h"

int texture_initialize(
        struct Texture2D *p_texture,
        int width,
        int height,
        const unsigned char *str_data
) {
        if (str_data == NULL) {
                fprintf(stderr, "[TEXTURE:INITIALIZE] -> No data provided: %s\n", p_texture->source);
                exit(EXIT_FAILURE);
        }

        glGenTextures(1, &p_texture->id);

        p_texture->width = width;
        p_texture->height = height;

        glGenTextures(1, &p_texture->id);
        glBindTexture(GL_TEXTURE_2D, p_texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, str_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        printf("[TEXTURE:INITIALIZE] -> Texture %s created\n", p_texture->source);

        return EXIT_SUCCESS;
}

int texture_bind(struct Texture2D *p_texture) {
        glBindTexture(GL_TEXTURE_2D, p_texture->id);
        return EXIT_SUCCESS;
}
