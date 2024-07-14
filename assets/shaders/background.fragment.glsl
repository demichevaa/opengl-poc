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
    fTexelColor.rgb *= 1 - vVertex.y * 0.15;
}
