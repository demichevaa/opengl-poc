#include "assets.h"

const char *ASSETS_ROOT_DIR = "./assets/";

int textureCreateFromAssets(Texture2D *texture, const char *assetRelativePath) {
        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, assetRelativePath);
        printf("[ASSETS:TEXTURE] -> Initializing texture from file: %s\n", file_name);


        stbi_set_flip_vertically_on_load(1);
        int width, height, nrChannels;
        unsigned char
            *data = stbi_load(file_name, &width, &height, &nrChannels, 4);

        textureInitialize(texture, width, height, data);
        textureBind(texture);

        printf("[ASSETS:TEXTURE] -> Texture %d loaded from: %s; (%d channels, %dx%d)\n",
               texture->id,
               file_name,
               nrChannels,
               width,
               height);

        stbi_image_free(data);

        return EXIT_SUCCESS;
}

char *assetGetContent(const char *assetRelativePath) {
        char file_name[1024];
        sprintf(file_name, "%s%s", ASSETS_ROOT_DIR, assetRelativePath);

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

int shaderCreateFromAssets(ShaderProgram *shader,
                           const char *vertexAssetRelativePath,
                           const char *fragmentAssetRelativePath,
                           const char *geometryAssetRelativePath) {
        char *vertexSource = assetGetContent(vertexAssetRelativePath);
        char *fragmentSource = assetGetContent(fragmentAssetRelativePath);

        char *geometrySource = NULL;
        if (geometryAssetRelativePath != NULL) {
                geometrySource = assetGetContent(geometryAssetRelativePath);
        }


        shaderProgramInitialize(shader,
                                vertexSource,
                                fragmentSource,
                                geometrySource);
        shader->vertexSourcePath = vertexAssetRelativePath;
        shader->fragmentSourcePath = fragmentAssetRelativePath;
        shader->geometrySourcePath = geometryAssetRelativePath;

        shaderProgramCompile(shader);

        printf(
            "[ASSETS:SHADER] -> Shader program %d compiled from: %s | %s | %s\n",
            shader->id,
            vertexAssetRelativePath,
            fragmentAssetRelativePath,
            geometryAssetRelativePath);

        return EXIT_SUCCESS;
}

int spriteCreateFromAssets(Sprite *sprite, const char *tag, const char *textureRelativePath) {
        // TODO: Create multiple sprites
        // TODO: Move to sprite initialize
        ShaderProgram *program = malloc(sizeof(ShaderProgram));
        shaderCreateFromAssets(program, "shaders/block.vertex.glsl", "shaders/block.fragment.glsl", NULL);

        Texture2D *texture = malloc(sizeof(Texture2D));
        textureCreateFromAssets(texture, textureRelativePath);

        spriteInitialize(sprite, tag, program, texture);
        printf(
            "[ASSETS:SPRITE] -> Sprite `%s` created for %s\n",
            sprite->tag,
            textureRelativePath
            );

        return EXIT_SUCCESS;
}
