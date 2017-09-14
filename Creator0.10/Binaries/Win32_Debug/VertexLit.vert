#version 430 core

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

uniform vec3 vLightPos;
uniform vec3 vEyePos;

uniform mat4 mModel;
uniform mat4 mModelViewProjection;

out vec2 texCoord;
out vec3 vLightDir;
out vec3 vEyeDir;
out vec3 oNormal;

void main()
{
	gl_Position = mModelViewProjection * vec4(vVertex, 1);	
	texCoord = vTexCoord;

	vec3 FragPos = vec3(mModel * vec4(vVertex, 1));
	vEyeDir = normalize(vEyePos - FragPos);
	vLightDir = normalize(vEyePos - FragPos);

	oNormal = normalize(vec3(mModel * vec4(vNormal, 1)));
}