#ifndef OPENGL_POC_PALETTE_H
#define OPENGL_POC_PALETTE_H

#include "cglm/cglm.h"

typedef struct {
    vec4 transparent;
    vec4 sandyBrown;
    /* Orange */
    vec4 outrageousOrange;
    /* Red */
    vec4 fireBrick;
    /* Dark grey */
    vec4 nevada;
    /* White grey */
    vec4 sandrift;
    /* Green */
    vec4 fruitSalad;
    /* Dark green */
    vec4 goblin;
    /* Dark color */
    vec4 cabSav;
    /* Sick blue */
    vec4 allports;
    /* Blue x green */
    vec4 keppel;
    /* Light Grey */
    vec4 zanah;
    /* Yellowish white */
    vec4 cherokee;
    /* Gold */
    vec4 goldTips;
    /* Orange brown */
    vec4 smokeTree;

} ColorsPalette;

static const ColorsPalette PALETTE = {
        .transparent = {1.0f, 1.0f, 1.0f, 1.0f},
        .sandyBrown = {0.96f, 0.60f, 0.39f, 1.0f},
        .outrageousOrange = {0.98f, 0.32f, 0.18f, 1.0f},
        .fireBrick = {0.71f, 0.16f, 0.16f, 1.0f},
        .nevada = {0.45f, 0.46f, 0.47f, 1.0f},
        .sandrift = {0.68f, 0.63f, 0.44f, 1.0f},
        .fruitSalad = {0.29f, 0.57f, 0.28f, 1.0f},
        .goblin = {0.22f, 0.34f, 0.25f, 1.0f},
        .cabSav = {0.33f, 0.20f, 0.23f, 1.0f},
        .allports = {0.12f, 0.48f, 0.55f, 1.0f},
        .keppel = {0.30f, 0.68f, 0.58f, 1.0f},
        .zanah = {0.67f, 0.76f, 0.67f, 1.0f},
        .cherokee = {0.96f, 0.80f, 0.56f, 1.0f},
        .goldTips = {0.89f, 0.67f, 0.18f, 1.0f},
        .smokeTree = {0.76f, 0.36f, 0.20f, 1.0f}
};

#endif //OPENGL_POC_PALETTE_H
