#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <malloc.h>

#include "texture.h"
#include "shader.h"
#include "sprite.h"

char *asset_get_content(const char *str_asset_relative_path);
int texture_create_from_assets(struct Texture2D *p_texture, const char *str_asset_relative_path);
int shader_create_from_assets(
        struct ShaderProgram *p_shader,
        const char *str_vertex_asset_relative_path,
        const char *str_fragment_asset_relative_path,
        const char *str_geometry_asset_relative_path
);
int sprite_create_from_assets(struct Sprite *p_sprite, const char *str_texture_relative_path);

const extern char *ASSETS_ROOT_DIR;

#endif // ASSETS_H
