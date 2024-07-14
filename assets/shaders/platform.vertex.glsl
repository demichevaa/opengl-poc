#version 330 core

layout (location = 0) in vec3 lPosition;
layout (location = 1) in vec2 lVertex;

uniform mat4 uMVP;

out vec2 vVertex;


void main()
{
   gl_Position = uMVP * vec4(lPosition, 1.0);
   vVertex = lVertex;
}
