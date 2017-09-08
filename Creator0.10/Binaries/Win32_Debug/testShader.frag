#version 430 core

in vec2 texCoord;

uniform mat4 mModelView;
uniform mat4 mModelViewProjection;

uniform vec3 vLightDir;
uniform vec3 vEyeDir;
uniform vec4 vBaseColor;

uniform sampler2D diffuse;
uniform sampler2D normal;

out vec4 fragColor;

void main()
{
	vec4 _vSurfaceColor = texture(diffuse, texCoord);

	vec3 _vLightDir = vLightDir;
	//Diffuse
	vec3 _vNormal = normalize(texture(normal, texCoord).rbg);	
	float _fDiffuse = max(dot(_vNormal, _vLightDir), 0.0);
	vec3 _vDiffuse = _vSurfaceColor.rgb * _fDiffuse;

	//vec3 _vReflectDir = reflect(vLightDir, _vNormal);
	//float spec = max(dot(vEyeDir, _vReflectDir), 0.0);
	//spec = pow(spec, 6.0);
	//spec *= 0.5;

	//_lightColor = min(_lightColor + spec, vec3(1));	
	fragColor = vec4(_vDiffuse, _vSurfaceColor.a);	
}