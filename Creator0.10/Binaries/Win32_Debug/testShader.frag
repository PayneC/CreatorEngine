#version 430 core

in vec4 color;
in vec2 texCoord;
in vec4 lightDirNormalize;
in vec4 normal;

uniform sampler2D texture0;

out vec4 fragColor;

void main()
{
	float NdotL = max(dot(normal, lightDirNormalize), 0.0);
	fragColor = texture(texture0, texCoord);
	fragColor = fragColor * color * NdotL;	
}