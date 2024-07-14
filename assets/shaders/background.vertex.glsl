#version 330 core

layout (location = 0) in vec3 lPosition;
layout (location = 1) in vec2 lVertex;

out vec2 vVertex;

uniform mat4 MVP;
uniform vec2 repeatFactor;

void main()
{
   vVertex = lVertex * repeatFactor;
   gl_Position = MVP * vec4(lPosition, 1.0);
}
