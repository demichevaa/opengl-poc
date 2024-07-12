#version 330 core

in vec2 TexCoords;
out vec4 color;
uniform sampler2D ourTexture;
uniform vec4 spriteColor;
uniform float textureAspectRatio;

void main()
{
    vec4 borderColor = vec4(0.65, 0.61, 0.60, 1.0);
    float borderWidth = 0.02f;

    bool isLeftBorder = TexCoords.x < borderWidth;
    bool isRightBorder = TexCoords.x > 1.0 - borderWidth;
    bool isTopBorder = TexCoords.y > 1.0 - borderWidth * textureAspectRatio;
    bool isBottomBorder = TexCoords.y < borderWidth * textureAspectRatio;

    if (isLeftBorder || isRightBorder || isTopBorder || isBottomBorder) {
        color = borderColor;
    }
    else {
        color = spriteColor * texture(ourTexture, TexCoords);
    }
}
