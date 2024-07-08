#include "viewport.h"

const float VIEWPORT_WIDTH = 160.0f;
const float VIEWPORT_HEIGHT = 90.0f;
const float VIEWPORT_ORIGIN =  0.0f;
const float VIEWPORT_ASPECT_RATIO = VIEWPORT_WIDTH / VIEWPORT_HEIGHT;

int viewportSetOrthogonalProjection(mat4 *p_projection) {
        const float screenWidth = 1366;  // Get the actual screen width
        const float screenHeight = 768; // Get the actual screen height
        const float screenAspect = screenWidth / screenHeight;
        float scale;
        if (screenAspect > VIEWPORT_ASPECT_RATIO) {
                // Screen is wider than game, fit game height to screen height
                scale = screenHeight / VIEWPORT_HEIGHT;
        } else {
                // Screen is narrower than game, fit game width to screen width
                scale = screenWidth / VIEWPORT_WIDTH;
        }

        // Calculate game size on screen
        float gameWidthOnScreen = VIEWPORT_WIDTH * scale;
        float gameHeightOnScreen = VIEWPORT_HEIGHT * scale;

        // Calculate offsets for centering the game on the screen
        float offsetX = (screenWidth - gameWidthOnScreen) / 2.0f;
        float offsetY = (screenHeight - gameHeightOnScreen) / 2.0f;

        glm_ortho(offsetX, offsetX + gameWidthOnScreen, offsetY, offsetY + gameHeightOnScreen, -1.0f, 1.0f, p_projection);

        //glm_ortho(0.0f, VIEWPORT_WIDTH, 0.0f, VIEWPORT_HEIGHT, -1.0f, 1.0f, (vec4 *) p_projection);
        return EXIT_SUCCESS;
}

int viewportEnable() {
        return EXIT_SUCCESS;
}
