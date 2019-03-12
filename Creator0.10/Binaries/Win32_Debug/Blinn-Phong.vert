#version 430 core

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec3 vTangent;

uniform vec3 vLightPos;
uniform vec3 vEyePos;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

uniform mat4 mModelViewProjection;

out vec2 texCoord;
out vec3 vLightDir;
out vec3 vEyeDir;

void main()
{
	gl_Position = mModelViewProjection * vec4(vVertex, 1);	
	texCoord = vTexCoord;

	mat3 normalMatrix = transpose(inverse(mat3(mModel)));
	//Get TBN space  
	vec3 N = normalize(normalMatrix * vNormal);
	vec3 T = normalize(normalMatrix * vTangent);
	vec3 B = cross(T, N);  
	
	mat3 TBN = transpose(mat3(T, B, N));

	vec3 FragPos = TBN * vec3(mModel * vec4(vVertex, 1));
	vEyeDir = normalize(TBN * vEyePos - FragPos);
	vLightDir = normalize(TBN * vEyePos - FragPos);
}