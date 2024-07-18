#version 330 core

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform float uEdgeHitBoxRatio;

in vec2 vVertex;

out vec4 fTexelColor;


void main()
{
    vec4 highlightColor = vec4(1.0, 0.0, 0.0, 1.0);
    float uEdgeHitBoxRatioY = 0.8f;


    bool isLeftEdge = vVertex.x <= uEdgeHitBoxRatio;
    bool isRightEdge = vVertex.x >= (1 - uEdgeHitBoxRatio);
    bool isTopEdge = vVertex.y >= uEdgeHitBoxRatioY;

    vec4 texel = texture(uTexture, vVertex);

    if ((isLeftEdge || isRightEdge) && isTopEdge) {
            texel.rgb = mix(texel.rgb, highlightColor.rgb, 0.5);
            fTexelColor = highlightColor * texel;
    } else if (isTopEdge) {
            texel.rgb = mix(texel.rgb, highlightColor.rgb, 0.5);
            fTexelColor = highlightColor * texel;
    }
    else {
        fTexelColor = uColor * texel;
    }
}
