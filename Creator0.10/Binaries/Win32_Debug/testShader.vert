#version 430 core

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

uniform mat4 mModelView;
uniform mat4 mModelViewProjection;

out vec2 texCoord;


void main()
{
	gl_Position = mModelViewProjection * vec4(vVertex, 1);	
	texCoord = vTexCoord;			
}