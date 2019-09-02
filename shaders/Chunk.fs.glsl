#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2DArray text;

void	main()
{
	FragColor = vec4(texture(text, vec3(TexCoords, 1)).rgb, 1);
}
