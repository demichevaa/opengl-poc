#version 330 core

in vec2 v_texturePosition;
out vec4 f_color;

uniform sampler2D image;
uniform vec3 color;

void main()
{
    f_color = vec4(color, 1.0) * texture(image, v_texturePosition);
}
