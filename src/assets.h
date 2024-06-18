#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <malloc.h>

#include "texture.h"
#include "shader.h"
#include "sprite.h"

char *assetGetContent(const char *assetName);
int textureCreateFromAssets(Texture2D *texture, const char *assetRelativePath);
int shaderCreateFromAssets(ShaderProgram *shader,
                           const char *vertexAssetRelativePath,
                           const char *fragmentAssetRelativePath,
                           const char *geometryAssetRelativePath);
int spriteCreateFromAssets(Sprite *sprite, const char *textureRelativePath);

#endif // ASSETS_H
