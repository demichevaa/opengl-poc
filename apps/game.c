#include "assets.h"

typedef enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
} GameState;

typedef struct GameObject {
        Texture2D texture;
        vec2 position;

} GameObject;
typedef struct Level {
        float ** data;

} Level;

