#include "ChunkManager.hpp"
#include "stb_image.h"
#include <algorithm>

ChunkManager::ChunkManager(std::shared_ptr<Shader> shader) : Renderer(shader)
{
	glGenTextures(1, &_text);

	int nbTexture = 8;
	int width, height, nrComponents;
	glBindTexture(GL_TEXTURE_2D_ARRAY, _text);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 4, GL_RGB8, 16, 16, nbTexture);
	for (int i = 0; i < nbTexture; i++)
	{
		std::string path = std::string(std::string("ressources/textures/minecraft/") + std::to_string(i) + std::string(".png"));
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, STBI_rgb);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float	halfRenderSize = RENDER_SIZE /2.0f;
	for (int i = -halfRenderSize; i < halfRenderSize; i++)
	{
		for (int j = -halfRenderSize; j < halfRenderSize; j++)
		{
			for (int k = -halfRenderSize; k < halfRenderSize; k++)
			{
				std::shared_ptr<Chunk> tmp(new Chunk(shader, Transform(glm::vec3(i * Chunk::CHUNK_SIZE, j * Chunk::CHUNK_SIZE, k * Chunk::CHUNK_SIZE)), _text));
				_chunkList.push_back(tmp);
				std::cout << i << std::endl;
			}
		}
	}
}

ChunkManager::~ChunkManager() {}

bool		sortChunk(const std::shared_ptr<Chunk> &first, const std::shared_ptr<Chunk> &sec)
{
	glm::vec3 camPos = Camera::instance->GetPos();
	return glm::distance(sec->transform.position, camPos) > glm::distance(first->transform.position, camPos);
}

void	ChunkManager::Draw() const
{
	for (auto it = _chunkToDraw.begin(); it != _chunkToDraw.end(); it++)
	{
		if ((*it)->IsLoad() && !(*it)->IsEmpty())
			(*it)->Draw();
	}
}

void ChunkManager::_CheckUnload(float & coord, float & dif, std::shared_ptr<Chunk> chunk)
{
	if (chunk->IsLoad())
	{
		coord += dif > 0 ? Chunk::CHUNK_SIZE * RENDER_SIZE : -Chunk::CHUNK_SIZE * RENDER_SIZE;
		chunk->Unload();
	}
}
void ChunkManager::Update()
{
	int chunkUpdated = 0;
	glm::vec3 camPos = Camera::instance->GetPos();
	_chunkList.sort(sortChunk);
	_chunkToDraw.clear();
	const int maxX = Chunk::CHUNK_SIZE * (RENDER_SIZE/ 2);
//	const int minX = Chunk::CHUNK_SIZE * (RENDER_SIZE / 2);
	const int maxY = Chunk::CHUNK_SIZE * (RENDER_SIZE / 2);
	const int maxZ = Chunk::CHUNK_SIZE * (RENDER_SIZE / 2);
	//const int minZ = Chunk::CHUNK_SIZE * (RENDER_SIZE / 2);
	//const float maxI = (RENDER_SIZE * RENDER_SIZE  * RENDER_SIZE );
	//int i = 0;
	auto end = _chunkList.end();
	for (auto it = _chunkList.begin(); /*i < maxI && */it != end; it++)
	{
		glm::vec3 dif = camPos - (*it)->transform.position;
		if (abs(dif.z) > maxZ)
			_CheckUnload((*it)->transform.position.z, dif.z, *it);
		if (abs(dif.y) > maxY)
			_CheckUnload((*it)->transform.position.y, dif.y, *it);
		if (abs(dif.x) > maxX)
			_CheckUnload((*it)->transform.position.x, dif.x, *it);
		if (!(*it)->IsLoad() && chunkUpdated < ASYNC_NUM_CHUNKS_PER_FRAME)
		{
			(*it)->UpdateMatrix();
			(*it)->SetUpChunk();
			(*it)->CreateMesh();
			chunkUpdated++;
		}
		_chunkToDraw.push_back(*it);
	//	i++;
	}
}

void ChunkManager::FixedUpdate()
{

}
