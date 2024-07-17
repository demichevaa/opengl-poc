#include "ui.h"
#include "assets.h"

int ui_initialize(struct UI *p_ui) {

        struct Texture2D *texture = malloc(sizeof(struct Texture2D));

        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, "textures/Grey_background_43.png");
        printf("[ASSETS:TEXTURE] -> Initializing texture from file: %s\n", file_name);

        stbi_set_flip_vertically_on_load(1);
        int width, height, nrChannels;
        unsigned char
                *data = stbi_load(file_name, &width, &height, &nrChannels, 4);


        texture_initialize(texture, width, height, data);
        texture_bind(texture);


        struct ShaderProgram *program = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(program, "shaders/background.vertex.glsl", "shaders/background.fragment.glsl", NULL);

        p_ui->background_tile = malloc(sizeof(struct Sprite));
        sprite_initialize(p_ui->background_tile, program, texture);
        p_ui->background_tile->height = VIEWPORT_HEIGHT;
        p_ui->background_tile->width = VIEWPORT_WIDTH;

        glm_vec4_copy((float *) &PALETTE.allports, p_ui->background_tile->color);

        return EXIT_SUCCESS;
}

int background_uniform_callback(struct Sprite *p_sprite) {
        vec2 repeat = {VIEWPORT_WIDTH / 10, VIEWPORT_HEIGHT / 10};

        shaderSetVec2f(p_sprite->p_shader, "uRepeatFactor", repeat);

        return EXIT_SUCCESS;
}

int ui_render(struct UI *p_ui) {

        sprite_render(p_ui->background_tile, (Callback) background_uniform_callback);
        return EXIT_SUCCESS;
}
