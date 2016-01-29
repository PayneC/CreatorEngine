#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
uniform mat4 MVP;

out vec4 color;

void main()
{
	gl_Position = MVP * vPosition;
	color = vColor;
}