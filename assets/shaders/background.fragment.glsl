#version 330 core

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform vec2 uRepeatFactor;

in vec2 vVertex;

out vec4 fTexelColor;


void main()
{
    vec4 texel = texture(uTexture, vVertex);
    vec3 blendedColor = mix(texel.rgb, uColor.rgb, 0.9);
    fTexelColor = vec4(blendedColor, texel.a);

    float gradientStartFromY = 0.3;
    float gradientIntensity = 0.15;
    fTexelColor.rgb *= gradientStartFromY + 1 - vVertex.y * gradientIntensity;
}
