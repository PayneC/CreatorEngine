#version 430 core

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

uniform mat4 mModelViewMatrix;
uniform vec4 vBaseColor;
uniform vec3 vLightDir;
uniform vec3 vEyeDir;

out vec4 color;
out vec2 texCoord;
out vec3 lightDirNormalize;
out vec3 normal;
out vec3 eyeDirNormalize;

void main()
{
	gl_Position = mModelViewMatrix * vec4(vVertex, 1);
	color = vBaseColor;
	texCoord = vTexCoord;
	lightDirNormalize = normalize(vLightDir);
	eyeDirNormalize = normalize(vEyeDir);
	normal = normalize(mModelViewMatrix * vec4(vNormal, 1)).rgb;
}