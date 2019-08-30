#include "Chunk.hpp"
#include <algorithm>
#include "glad.h"
#include <iostream>
#include "stdlib.h"

Chunk::Chunk(void) : Renderer()
{
    glGenVertexArrays(1, &_vao);
    
    return;
}
    
Chunk::Chunk(std::shared_ptr<Shader> shader, Transform transform) : Renderer(shader, transform)
{
	SetUpChunk();
    CreateMesh();
    return;
}
void	Chunk::SetUpChunk()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (y + transform.position.y > 8)
					_blocks[x][y][z].SetActive(false);
			}
		}
	}
}

void	Chunk::Unload()
{
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_vao);
	_vertices.clear();
	_indices.clear();
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
				_blocks[x][y][z].SetActive(true);
		}
	}
}
Chunk::~Chunk()
{
	Unload();
}

void	Chunk::CreateMesh()
{
	bool lDefault = false;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (!_blocks[x][y][z].IsActive())
					continue;

				bool lXNegative = lDefault;
				if (x > 0)
					lXNegative = _blocks[x - 1][y][z].IsActive();

				bool lXPositive = lDefault;
				if (x < CHUNK_SIZE - 1)
					lXPositive = _blocks[x + 1][y][z].IsActive();

				bool lYNegative = lDefault;
				if (y > 0)
					lYNegative = _blocks[x][y - 1][z].IsActive();

				bool lYPositive = lDefault;
				if (y < CHUNK_SIZE - 1)
					lYPositive = _blocks[x][y + 1][z].IsActive();

				bool lZNegative = lDefault;
				if (z > 0)
					lZNegative = _blocks[x][y][z - 1].IsActive();

				bool lZPositive = lDefault;
				if (z < CHUNK_SIZE - 1)
					lZPositive = _blocks[x][y][z + 1].IsActive();

				_CreateCube(lXNegative, lXPositive, lYNegative, lYPositive, lZNegative, lZPositive, x, y, z);
			}
		}
	}
	_SendToOpenGL();
}
void	Chunk::_CreateCube(bool lXNegative, bool lXPositive, bool lYNegative, bool lYPositive, bool lZNegative, bool lZPositive, float x, float y, float z)
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

	std::vector<unsigned int> indices;
	std::vector<unsigned int> front = {
		0, 1, 2,
		2, 1, 3
	};
	std::vector<unsigned int> top = {
		2, 3, 4,
		4, 3, 5
	};
	std::vector<unsigned int> back = {
		4, 5, 6,
		6, 5, 7
	};
	std::vector<unsigned int> bottom = {
		6, 7, 0,
		0, 7, 1
	};
	std::vector<unsigned int> right = {
		1, 7, 3,
		3, 7, 5
	};
	std::vector<unsigned int> left = {
		6, 0, 4,
		4, 0, 2
	};

	if (!lZNegative)
		indices.insert(indices.end(), back.begin(), back.end());
	if (!lZPositive)
		indices.insert(indices.end(), front.begin(), front.end());

	if (!lXNegative)
		indices.insert(indices.end(), left.begin(), left.end());
	if (!lXPositive)
		indices.insert(indices.end(), right.begin(), right.end());

	if (!lYNegative)
		indices.insert(indices.end(), bottom.begin(), bottom.end());
	if (!lYPositive)
		indices.insert(indices.end(), top.begin(), top.end());

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
	_shader->setMat4("model", _modelMatrix);

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
