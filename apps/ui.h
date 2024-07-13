#ifndef OPENGL_POC_UI_H
#define OPENGL_POC_UI_H

#include "texture.h"
#include "collections.h"
#include "sprite.h"

typedef struct UI {
    struct LinkedList  *layoutTextures;
    struct LinkedList *layoutSprites;
    Sprite *backgroundTile;
} UI;

int uiInitialize(UI *p_ui);
int uiRender(UI *p_ui);

#endif //OPENGL_POC_UI_H
