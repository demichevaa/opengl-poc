#include "assets.h"

const char *ASSETS_ROOT_DIR = "./assets/";

int texture_create_from_assets(struct Texture2D *p_texture, const char *str_asset_relative_path) {
        if (p_texture == NULL) {
                return EXIT_FAILURE;
        }

        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, str_asset_relative_path);
        printf("[ASSETS:TEXTURE] -> Initializing texture from file: %s\n", file_name);


        stbi_set_flip_vertically_on_load(1);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 4);

        texture_initialize(p_texture, width, height, data);
        texture_bind(p_texture);

        printf(
                "[ASSETS:TEXTURE] -> Texture %d loaded from: %s; (%d channels, %dx%d)\n",
                p_texture->id,
                file_name,
                nrChannels,
                width,
                height
        );

        stbi_image_free(data);

        return EXIT_SUCCESS;
}

char *asset_get_content(const char *str_asset_relative_path) {
        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, str_asset_relative_path);

        FILE *file = fopen(file_name, "r");
        if (file == NULL) {
                printf("Could not open file %s\n", file_name);
                return NULL;
        }

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *content = malloc(size + 1);
        if (content == NULL) {
                printf("Could not allocate memory for file content\n");
                fclose(file);
                return NULL;
        }

        fread(content, 1, size, file);

        content[size] = '\0';

        fclose(file);

        return content;
}

int shader_create_from_assets(
        struct ShaderProgram *p_shader,
        const char *str_vertex_asset_relative_path,
        const char *str_fragment_asset_relative_path,
        const char *str_geometry_asset_relative_path
) {
        if (p_shader == NULL) {
                return EXIT_FAILURE;
        }

        char *str_vertex_source = asset_get_content(str_vertex_asset_relative_path);
        char *str_fragment_source = asset_get_content(str_fragment_asset_relative_path);

        char *str_geometry_source = NULL;
        if (str_geometry_asset_relative_path != NULL) {
                str_geometry_source = asset_get_content(str_geometry_asset_relative_path);
        }


        shader_initialize(p_shader, str_vertex_source, str_fragment_source, str_geometry_source);
        p_shader->str_vertex_source_path = str_vertex_asset_relative_path;
        p_shader->str_fragment_source_path = str_fragment_asset_relative_path;
        p_shader->str_geometry_source_path = str_geometry_asset_relative_path;

        shader_compile(p_shader);

        printf(
                "[ASSETS:SHADER] -> Shader program %d compiled from: %s | %s | %s\n",
                p_shader->id,
                str_vertex_asset_relative_path,
                str_fragment_asset_relative_path,
                str_geometry_asset_relative_path
        );

        return EXIT_SUCCESS;
}

int sprite_create_from_assets(struct Sprite *p_sprite, const char *str_texture_relative_path) {
        struct ShaderProgram *p_shader = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(p_shader, "shaders/block.vertex.glsl", "shaders/block.fragment.glsl", NULL);

        struct Texture2D *p_texture = malloc(sizeof(struct Texture2D));
        texture_create_from_assets(p_texture, str_texture_relative_path);

        sprite_initialize(p_sprite, p_shader, p_texture);

        return EXIT_SUCCESS;
}
