#include "ui.h"
#include "assets.h"

int uiInitialize(UI *p_ui) {
        p_ui->layoutTextures = llInitialize();

        Texture2D *texture = malloc(sizeof(Texture2D));

        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, "textures/Grey_background_43.png");
        printf("[ASSETS:TEXTURE] -> Initializing texture from file: %s\n", file_name);


        stbi_set_flip_vertically_on_load(1);
        int width, height, nrChannels;
        unsigned char
                *data = stbi_load(file_name, &width, &height, &nrChannels, 4);


        textureInitialize(texture, width, height, data);
        textureBind(texture);


        ShaderProgram *program = malloc(sizeof(ShaderProgram));
        shaderCreateFromAssets(program, "shaders/background.vertex.glsl", "shaders/background.fragment.glsl", NULL);

        p_ui->backgroundTile = malloc(sizeof(Sprite));
        spriteInitialize(p_ui->backgroundTile, "background", program, texture);
        p_ui->backgroundTile->height = VIEWPORT_HEIGHT;
        p_ui->backgroundTile->width = VIEWPORT_WIDTH;

        glm_vec4_copy((float *) &PALETTE.allports, p_ui->backgroundTile->color);

        return EXIT_SUCCESS;
}

int backgroundUniformCallback(Sprite *sprite) {
        vec2 repeat = {VIEWPORT_WIDTH / 10, VIEWPORT_HEIGHT / 10};

        shaderSetVec2f(sprite->shader, "repeatFactor", repeat);

        return EXIT_SUCCESS;
}

int uiRender(UI *p_ui) {

        spriteRender(p_ui->backgroundTile, (Callback) backgroundUniformCallback);
        return EXIT_SUCCESS;
}
