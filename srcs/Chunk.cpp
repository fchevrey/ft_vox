#include "Chunk.hpp"
#include <algorithm>
#include "glad.h"
#include <iostream>
#include "stdlib.h"
#include "World.hpp"
Chunk::Chunk(void) : Renderer()
{
    glGenVertexArrays(1, &_vao);
    
    return;
}
    
Chunk::Chunk(std::shared_ptr<Shader> shader, Transform transform, unsigned int texture) : Renderer(shader, transform), _text(texture), _isLoad(false), _hasMesh(false), _isSetUp(false), _isEmpty(false)
{
	glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_vao);
	SetUpChunk();
    CreateMesh();
    return;
}
void	Chunk::SetUpChunk()
{
	int i = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			float test;
			if (transform.position.y >= 0)
				test = abs(World::out.GetNoise(x + transform.position.x, z + transform.position.z) * 200);
			else
				test = 0;
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				if (y + transform.position.y >= 0)
				{
					if (test < y + transform.position.y)
						_blocks[x][y][z].SetActive(false);
					else if (y + transform.position.y > 70)
						_blocks[x][y][z].SetType(Snow);
					else if (y + transform.position.y > 10 && y + transform.position.y < 15)
						_blocks[x][y][z].SetType(Sand);
					else if (y + transform.position.y <= 10 && y + transform.position.y >= 0)
						_blocks[x][y][z].SetType(Water);
				}
				else if (y + transform.position.y < -1 && World::in.GetNoise(x + transform.position.x, y + transform.position.y, z + transform.position.z) > 0)
					_blocks[x][y][z].SetActive(false);

				if (!_blocks[x][y][z].IsActive())
					i++;
			}
		}
	}
	if (i == CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)
		_isEmpty = true;
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
			{
				_blocks[x][y][z].SetActive(true);
				_blocks[x][y][z].SetType(Grass);
			}
		}
	}
	_isLoad = false;
	_hasMesh = false;
	_isSetUp = false;
	_isEmpty = false;
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

bool	Chunk::IsEmpty() const { return _isEmpty; }

bool	Chunk::_CheckBlock(float x, float y, float z)
{
	if (y >= 0)
	{
		if (abs(World::out.GetNoise(x, z) * 200) < y)
			return false;
		else
			return true;
	}
	else if (y < -1)
	{
		if (World::in.GetNoise(x, y, z) > 0)
			return false;
		else
			return true;
	}
	else
		return true;
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

				glm::vec3 worldPos = glm::vec3(x, y, z) + transform.position;

				bool lXNegative = lDefault;
				if (x > 0)
					lXNegative = _blocks[x - 1][y][z].IsActive();
				else
					lXNegative = _CheckBlock(worldPos.x - 1, worldPos.y, worldPos.z);

				bool lXPositive = lDefault;
				if (x < CHUNK_SIZE - 1)
					lXPositive = _blocks[x + 1][y][z].IsActive();
				else
					lXPositive = _CheckBlock(worldPos.x + 1, worldPos.y, worldPos.z);

				bool lYNegative = lDefault;
				if (y > 0)
					lYNegative = _blocks[x][y - 1][z].IsActive();
				else
					lYNegative = _CheckBlock(worldPos.x, worldPos.y - 1, worldPos.z);

				bool lYPositive = lDefault;
				if (y < CHUNK_SIZE - 1)
					lYPositive = _blocks[x][y + 1][z].IsActive();
				else
					lYPositive = _CheckBlock(worldPos.x, worldPos.y + 1, worldPos.z);

				bool lZNegative = lDefault;
				if (z > 0)
					lZNegative = _blocks[x][y][z - 1].IsActive();
				else
					lZNegative = _CheckBlock(worldPos.x, worldPos.y, worldPos.z - 1);

				bool lZPositive = lDefault;
				if (z < CHUNK_SIZE - 1)
					lZPositive = _blocks[x][y][z + 1].IsActive();
				else
					lZPositive = _CheckBlock(worldPos.x, worldPos.y, worldPos.z + 1);

				_CreateCube(lXNegative, lXPositive, lYNegative, lYPositive, lZNegative, lZPositive, x, y, z);
			}
		}
	}
	_hasMesh = true;
	_SendToOpenGL();
}

float	Chunk::_GetTexture(glm::vec3 normal, eBlockType type)
{
	if (type == Grass)
	{
		if (normal == glm::vec3(0.0f, 1.0f, 0.0f))
				return 0.0f;
		if (normal == glm::vec3(0.0f, -1.0f, 0.0f))
				return 2.0f;
		if (normal == glm::vec3(1.0f, 0.0f, 0.0f) || normal == glm::vec3(-1.0f, 0.0f, 0.0f) || normal == glm::vec3(0.0f, 0.0f, 1.0f) || normal == glm::vec3(0.0f, 0.0f, -1.0f))
				return 3.0f;
	}
	if (type == Snow)
	{
	{
		if (normal == glm::vec3(0.0f, 1.0f, 0.0f))
				return 7.0f;
		if (normal == glm::vec3(0.0f, -1.0f, 0.0f))
				return 2.0f;
		if (normal == glm::vec3(1.0f, 0.0f, 0.0f) || normal == glm::vec3(-1.0f, 0.0f, 0.0f) || normal == glm::vec3(0.0f, 0.0f, 1.0f) || normal == glm::vec3(0.0f, 0.0f, -1.0f))
				return 6.0f;
	}
	}
	if (type == Dirt)
		return 2.0f;
	if (type == Water)
		return 5.0f;
	if (type == Stone)
		return 1.0f;
	if (type == Sand)
		return 4.0f;
	return 0.0f;
}

void	Chunk::_AddFront(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddBack(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(0.0f, 0.0f, -1.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddTop(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x-halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddBottom(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(0.0f, -1.0f, 0.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z+halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddLeft(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x-halfBlock, y-halfBlock, z-halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z-halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y-halfBlock, z+halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x-halfBlock, y+halfBlock, z+halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z
	};

	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void	Chunk::_AddRight(float x, float y, float z, float halfBlock)
{
	glm::vec3 normal = glm::vec3(1.0f, 0.0f, 0.0f);
	float texture = _GetTexture(normal, _blocks[static_cast<int>(x)][static_cast<int>(y)][static_cast<int>(z)].GetType());
	std::vector<float> vertices = {
		x+halfBlock, y-halfBlock, z-halfBlock, 1.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z-halfBlock, 1.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y+halfBlock, z+halfBlock, 0.0f, 0.0f, texture, normal.x, normal.y, normal.z,
		x+halfBlock, y-halfBlock, z+halfBlock, 0.0f, 1.0f, texture, normal.x, normal.y, normal.z
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 6));

	glBindVertexArray(0);
	_isLoad = true;
}

void	Chunk::Draw() const
{
	//glCullFace(GL_BACK);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _text);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_shader->use();
	_shader->setMat4("view", Camera::instance->GetMatView());
	_shader->setMat4("projection", Camera::instance->GetMatProj());
	_shader->setMat4("model", _modelMatrix);
	_shader->setVec3("uCamPos", Camera::instance->GetPos());
	_shader->setInt("text", 0);

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 9.0f);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
