#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 MVP;
uniform vec4 BaseColor;

out vec4 Color;
out vec2 TexCoord;

void main()
{
	gl_Position = MVP * vec4(position, 1);
	Color = BaseColor;
	TexCoord = texCoord;
}