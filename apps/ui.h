#ifndef OPENGL_POC_UI_H
#define OPENGL_POC_UI_H

#include "texture.h"
#include "collections.h"
#include "sprite.h"

struct UI {
    struct Sprite *background_tile;
};

int ui_initialize(struct UI *p_ui);
int ui_render(struct UI *p_ui);

#endif //OPENGL_POC_UI_H
