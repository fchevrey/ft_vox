#version 330 core

uniform sampler2D	tex;
uniform vec4		color;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1);//texture(tex, TexCoord) * color;
}
