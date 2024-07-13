#version 330 core

in vec2 TexCoords;
out vec4 color;
uniform sampler2D ourTexture;
uniform vec4 spriteColor;

void main()
{
    color = spriteColor * texture(ourTexture, TexCoords);
}
