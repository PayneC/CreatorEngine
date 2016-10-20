#version 430 core

in vec4 Color;
in vec2 TexCoord;

out vec4 fColor;
uniform sampler2D ourTexture;

void main()
{
	fColor = texture(ourTexture, TexCoord) * Color;
}