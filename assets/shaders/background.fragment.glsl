#version 330 core

in vec2 vVertex;
out vec4 fColor;

uniform sampler2D ourTexture;
uniform vec4 spriteColor;

void main()
{
    vec2 bottomCenter = vec2(0.5, 0.0);
    float distance = distance(vVertex, bottomCenter);
    float gradient = clamp(distance * 2.0, 0.0, 1.0);

    vec4 textureColor = texture(ourTexture, vVertex);
    vec3 blendedColor = mix(textureColor.rgb, spriteColor.rgb, gradient);
    fColor = vec4(blendedColor, textureColor.a);
    //color.rgb *= (vVertex.x * vVertex.y);
}
