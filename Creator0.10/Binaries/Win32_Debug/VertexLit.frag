#version 430 core

in vec2 texCoord;
in vec3 vLightDir;
in vec3 vEyeDir;
in vec3 oNormal;

uniform vec4 vBaseColor;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 fragColor;

void main()
{
	float shininess = 64f;

	vec3 lightAmbient = vec3(0.2, 0.2, 0.2);
	vec3 lightDiffuse = vec3(0.5, 0.5, 0.5);
	vec3 lightSpecular = vec3(1.0, 1.0, 1.0);	

	vec4 _vSurfaceColor = texture(diffuse, texCoord);
	vec3 _vDiffuseColor = _vSurfaceColor.rgb;
	vec3 _vSpecularColor = texture(specular, texCoord).rgb;

	vec3 _vAmbient = lightAmbient * _vDiffuseColor;

	vec3 _vLightDir = vLightDir;
	float _fDiffuse = max(dot(oNormal, _vLightDir), 0.0);
	vec3 _vDiffuse =  lightDiffuse * _fDiffuse * _vDiffuseColor;

    vec3 _vEyeDir = vEyeDir;
	vec3 _vReflectDir = reflect(-_vLightDir, oNormal);
	float _fSpec = pow(max(dot(_vEyeDir, _vReflectDir), 0.0), shininess);
	vec3 _vSpecular = lightSpecular * _fSpec * _vSpecularColor;

	fragColor = vec4(_vSpecular + _vDiffuse + _vAmbient, _vSurfaceColor.a);	
}