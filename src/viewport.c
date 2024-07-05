#include "viewport.h"

const float GAME_WIDTH = 160.0f;
const float GAME_HEIGHT = 90.0f;
const float GAME_ASPECT = GAME_WIDTH / GAME_HEIGHT;

int viewportSetOrthogonalProjection(mat4 *p_projection) {
        const float screenWidth = 1366;  // Get the actual screen width
        const float screenHeight = 768; // Get the actual screen height
        const float screenAspect = screenWidth / screenHeight;
        float scale;
        if (screenAspect > GAME_ASPECT) {
                // Screen is wider than game, fit game height to screen height
                scale = screenHeight / GAME_HEIGHT;
        } else {
                // Screen is narrower than game, fit game width to screen width
                scale = screenWidth / GAME_WIDTH;
        }

        // Calculate game size on screen
        float gameWidthOnScreen = GAME_WIDTH * scale;
        float gameHeightOnScreen = GAME_HEIGHT * scale;

        // Calculate offsets for centering the game on the screen
        float offsetX = (screenWidth - gameWidthOnScreen) / 2.0f;
        float offsetY = (screenHeight - gameHeightOnScreen) / 2.0f;

        glm_ortho(offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f, p_projection);

        //glm_ortho(0.0f, GAME_WIDTH, 0.0f, GAME_HEIGHT, -1.0f, 1.0f, (vec4 *) p_projection);
        return EXIT_SUCCESS;
}

int viewportEnable() {
        return EXIT_SUCCESS;
}
