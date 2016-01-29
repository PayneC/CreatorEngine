#version 430 core

layout(location = 0) in vec4 vPosition;

uniform vec4 AnchorPoint;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * (vPosition - AnchorPoint);
}