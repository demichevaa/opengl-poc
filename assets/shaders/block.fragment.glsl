#version 330 core

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform float uTextureAspectRatio;

in vec2 vVertex;

out vec4 fTexelColor;


void main()
{
    vec4 borderColor = vec4(0.65, 0.61, 0.60, 1.0);
    float borderWidth = 0.02f;

    bool isLeftBorder = vVertex.x < borderWidth;
    bool isRightBorder = vVertex.x > 1.0 - borderWidth;
    bool isTopBorder = vVertex.y > 1.0 - borderWidth * uTextureAspectRatio;
    bool isBottomBorder = vVertex.y < borderWidth * uTextureAspectRatio;

    if (isLeftBorder || isRightBorder || isTopBorder || isBottomBorder) {
        fTexelColor = borderColor;
    }
    else {
        fTexelColor = uColor * texture(uTexture, vVertex);
    }
}
