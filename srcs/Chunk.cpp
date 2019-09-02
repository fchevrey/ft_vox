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
    
Chunk::Chunk(std::shared_ptr<Shader> shader, Transform transform, unsigned int texture) : Renderer(shader, transform), _text(texture), _isLoad(false), _hasMesh(false), _isSetUp(false)
{
	glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_vao);
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
	_isSetUp = true;
}

void	Chunk::Unload()
{
	_vertices.clear();
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
				_blocks[x][y][z].SetActive(true);
		}
	}
	_isLoad = false;
	_hasMesh = false;
	_isSetUp = false;
}
Chunk::~Chunk()
{
	Unload();
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_vao);
}

bool	Chunk::IsLoad() const { return _isLoad; }

bool	Chunk::HasMesh() const { return _hasMesh; }

bool	Chunk::IsSetUp() const { return _isSetUp; }

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
	_hasMesh = true;
	_SendToOpenGL();
}

void	Chunk::_AddFront(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f,
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f,
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddBack(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f,
		x+halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f,
		x+halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f,
		x+halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddTop(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 1.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 1.0f,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 1.0f,
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddBottom(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z+halfBlock, 0.0f, 0.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 0.0f,
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f,
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 0.0f,
		x+halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f,
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddLeft(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f,
		x-halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f,
		x-halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f,
		x-halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f,
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddRight(float x, float y, float z, float halfBlock)
{
	std::vector<float> vertices = {
		x+halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f,
		x+halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f,
		x+halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f,
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_CreateCube(bool lXNegative, bool lXPositive, bool lYNegative, bool lYPositive, bool lZNegative, bool lZPositive, float x, float y, float z)
{
	float halfBlock = Block::BLOCK_SIZE / 2.0f;

	if (!lZNegative)
		_AddBack(x, y, z, halfBlock);
	if (!lZPositive)
		_AddFront(x, y, z, halfBlock);

	if (!lXNegative)
		_AddLeft(x, y, z, halfBlock);
	if (!lXPositive)
		_AddRight(x, y, z, halfBlock);

	if (!lYNegative)
		_AddBottom(x, y, z, halfBlock);
	if (!lYPositive)
		_AddTop(x, y, z, halfBlock);

}

void	Chunk::_SendToOpenGL()
{
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	glBindVertexArray(0);
	_isLoad = true;
}

void	Chunk::Draw() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _text);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_shader->use();
	_shader->setMat4("view", Camera::instance->GetMatView());
	_shader->setMat4("projection", Camera::instance->GetMatProj());
	_shader->setMat4("model", _modelMatrix);
	_shader->setInt("text", 0);

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 5.0f);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
