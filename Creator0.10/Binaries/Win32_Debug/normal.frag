#version 430 core

in vec4 color;
in vec2 texCoord;
in vec4 lightDirNormalize;
in vec4 normal;

uniform sampler2D texture0;
uniform sampler2D textureN;

out vec4 fragColor;

void main()
{
	vec4 _normal = texture(textureN, texCoord);
	float NdotL = max(dot(_normal, lightDirNormalize), 0.0);
	fragColor = texture(texture0, texCoord);
	fragColor = fragColor * color * NdotL;	
}