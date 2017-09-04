#version 430 core

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

uniform mat4 mModelViewMatrix;
uniform vec4 vBaseColor;
uniform vec3 vLightDir;

out vec4 color;
out vec2 texCoord;
out vec4 lightDirNormalize;
out vec4 normal;

void main()
{
	gl_Position = mModelViewMatrix * vec4(vVertex, 1);
	color = vBaseColor;
	texCoord = vTexCoord;
	lightDirNormalize = normalize(vec4(vLightDir, 1));
	normal = normalize(mModelViewMatrix * vec4(vNormal, 1));
}