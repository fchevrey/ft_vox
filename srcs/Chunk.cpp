#include "Chunk.hpp"
#include "Block.hpp"
#include <algorithm>
#include "glad.h"
#include <vector>
#include "Camera.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "stdlib.h"
Chunk::Chunk()
{
	std::vector<const char *>	shadersPath{"shaders/Vertex.vs.glsl", "shaders/Chunk.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_shader = new Shader(shadersPath, type);

	CreateMesh();
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_vao);
	delete _shader;
}

void	Chunk::CreateMesh()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (_blocks[x][y][z].IsActive())
					_CreateCube(x, y, z);
			}
		}
	}
	_SendToOpenGL();
}
#include <iostream>
void	Chunk::_CreateCube(float x, float y, float z)
{
	float halfBlock = Block::BLOCK_SIZE / 2.0f;
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z+halfBlock,
		x+halfBlock, y-halfBlock, z+halfBlock,
		x-halfBlock, y+halfBlock, z+halfBlock,
		x+halfBlock, y+halfBlock, z+halfBlock,
		x-halfBlock, y+halfBlock, z-halfBlock,
		x+halfBlock, y+halfBlock, z-halfBlock,
		x-halfBlock, y-halfBlock, z-halfBlock,
		x+halfBlock, y-halfBlock, z-halfBlock
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		1, 7, 3,
		3, 7, 5,
		6, 0, 4,
		4, 0, 2
	};

	for (unsigned int& n : indices)
		n += static_cast<unsigned int>(_vertices.size()) / 3.0f;
	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
	_indices.insert(_indices.end(), indices.begin(), indices.end());
}

void	Chunk::_SendToOpenGL()
{
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindVertexArray(0);
}

void	Chunk::Draw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_shader->use();
	_shader->setMat4("view", Camera::instance->GetMatView());
	_shader->setMat4("projection", Camera::instance->GetMatProj());
	_shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
