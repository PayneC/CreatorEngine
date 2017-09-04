#version 430 core

in vec4 color;
in vec2 texCoord;
in vec3 lightDirNormalize;
in vec3 eyeDirNormalize;
in vec3 normal;

uniform sampler2D texture0;
uniform sampler2D textureN;

out vec4 fragColor;

void main()
{
	vec4 surfaceColor = texture(texture0, texCoord);
	vec3 _normal = texture(textureN, texCoord).rbg;
	
	float NdotL = max(dot(_normal, lightDirNormalize), 0.0);
	vec3 _lightColor = surfaceColor.rgb * NdotL;

	vec3 reflectDir = reflect(lightDirNormalize, _normal);
	float spec = max(dot(eyeDirNormalize, reflectDir), 0.0);
	spec = pow(spec, 6.0);
	spec *= 0.5;

	_lightColor = min(_lightColor + spec, vec3(1));	
	fragColor = vec4(_lightColor, surfaceColor.a);	
}