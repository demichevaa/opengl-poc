#version 330 core

uniform sampler2D uTexture;
uniform vec4 uColor;

in vec2 vVertex;

out vec4 fTexelColor;


void main()
{
    fTexelColor = uColor * texture(uTexture, vVertex);
}
