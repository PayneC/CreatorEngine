#version 430 core

layout(location = 0) in vec4 vVertex;
layout(location = 3) in vec4 vNormal;
layout(location = 2) in vec4 vUV;
layout(location = 1) in vec4 vColor;

uniform mat4 MVP;
uniform vec4 BaseColor;

out vec4 color;

void main()
{
	gl_Position = MVP * vVertex;
	color = BaseColor;
}