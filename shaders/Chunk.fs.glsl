#version 330 core

out vec4 FragColor;
in vec3 TexCoords;
in vec3 Normal;
in vec3 Pos;

uniform sampler2DArray text;
uniform vec3 uCamPos;

void	main()
{
	FragColor = vec4(texture(text, vec3(TexCoords.xy, TexCoords.z)).rgb, 1);
}
