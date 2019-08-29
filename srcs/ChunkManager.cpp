#include "ChunkManager.hpp"

ChunkManager::ChunkManager(std::shared_ptr<Shader> shader)
{
	float	halfRenderSize = RENDER_SIZE / 2.0f;
	for (int i = -halfRenderSize; i < halfRenderSize; i++)
	{
		for (int j = -halfRenderSize; j < halfRenderSize; j++)
		{
			for (int k = -halfRenderSize; k < halfRenderSize; k++)
			{
				std::shared_ptr<Chunk> tmp(new Chunk(shader, Transform(glm::vec3(i * Chunk::CHUNK_SIZE, j * Chunk::CHUNK_SIZE, k * Chunk::CHUNK_SIZE))));
				_chunkList.push_back(tmp);
				std::cout << i << std::endl;
			}
		}
	}
}

ChunkManager::~ChunkManager() {}

void	ChunkManager::Draw()
{
	for (auto it = _chunkList.begin(); it != _chunkList.end(); it++)
		(*it)->Draw();
}
