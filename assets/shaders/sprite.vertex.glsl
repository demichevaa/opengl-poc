#version 330 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 texturePosition;

out vec2 v_texturePosition;

uniform mat3 transform;
uniform mat3 projection;
uniform float aspectRatio;

void main()
{
        gl_Position = vec4(transform * vec3(vertexPosition, 1.0), 1.0);
        //gl_Position.x *= aspectRatio;
        v_texturePosition = texturePosition;
}
