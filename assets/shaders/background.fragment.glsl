#version 330 core

in vec2 TexCoords;
out vec4 color;
uniform sampler2D ourTexture;
uniform vec4 spriteColor;

void main()
{

    vec4 textureColor = texture(ourTexture, TexCoords);
    vec3 blendedColor = mix(textureColor.rgb, spriteColor.rgb, 0.9);
    color = vec4(blendedColor, textureColor.a);
    color.rgb *= 0.5;
}
