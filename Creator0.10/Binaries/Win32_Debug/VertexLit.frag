#version 430 core

in vec2 texCoord;
in vec3 vLightDir;
in vec3 vEyeDir;

uniform vec4 vBaseColor;

uniform sampler2D diffuse;
uniform sampler2D normal;

out vec4 fragColor;

void main()
{
	float _speclarStrength = 0.5f;
	

	vec3 oNormal = texture(normal, texCoord).rgb;
	oNormal = normalize(oNormal * 2.0 - 1.0);       

	vec4 _vSurfaceColor = texture(diffuse, texCoord);

	vec3 _lightColor = _vSurfaceColor.rgb;

	vec3 ambient = 0.1 * _lightColor;

	vec3 _vLightDir = vLightDir;//normalize(-FragPos);//vLightDir;
	float _fDiffuse = max(dot(oNormal, _vLightDir), 0.0);
	vec3 _vDiffuse = _lightColor * _fDiffuse;

    vec3 _vEyeDir = vEyeDir;//normalize(-FragPos);
	vec3 _vReflectDir = reflect(-_vLightDir, oNormal);

	float _fSpec = pow(max(dot(_vEyeDir, _vReflectDir), 0.0), 32);
	vec3 _vSpecular = vec3(0.2) * _fSpec;

	//vec3 _rlt = (_vSpecular + _vDiffuse + ambient) * _vSurfaceColor.rgb;

	fragColor = vec4(_vSpecular + _vDiffuse + ambient, _vSurfaceColor.a);	
}