#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 atexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
out mat4 viewMat;
out mat4 invertViewMat;
out mat4 invertProjMat;

void main()
{
	TexCoords = atexCoord;
	invertViewMat = inverse(view);
	invertProjMat = inverse(projection);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
