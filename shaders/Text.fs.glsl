#version 330 core

uniform sampler2D	tex;
uniform vec4		color;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	FragColor = color * vec4(1.0, 1.0, 1.0, texture(tex, TexCoord).r);
}
