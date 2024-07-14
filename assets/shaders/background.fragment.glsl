#version 330 core

uniform sampler2D uTexture;
uniform vec4 uColor;

in vec2 vVertex;

out vec4 fTexelColor;


void main()
{
    vec2 bottomCenter = vec2(0.5, 0.0);
    float distance = distance(vVertex, bottomCenter);
    float gradient = clamp(distance * 2.0, 0.0, 1.0);

    vec4 textureColor = texture(uTexture, vVertex);
    vec3 blendedColor = mix(textureColor.rgb, uColor.rgb, gradient);
    fTexelColor = vec4(blendedColor, textureColor.a);
    //color.rgb *= (vVertex.x * vVertex.y);
}
