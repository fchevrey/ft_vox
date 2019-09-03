#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

uniform sampler2DArray text;

void	main()
{
	FragColor = vec4(texture(text, vec3(TexCoords.xy, TexCoords.z)).rgb, 1);
}
