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

void ChunkManager::Update()
{
	int chunkUpdated = 0;
	for (auto it = _chunkList.begin(); it != _chunkList.end(); it++)
	{
		glm::vec3 dif = Camera::instance->GetPos() - (*it)->transform.position;
		if (abs(dif.z) > Chunk::CHUNK_SIZE * (RENDER_SIZE / 2))
		{
			(*it)->transform.position.z += dif.z > 0 ? Chunk::CHUNK_SIZE * RENDER_SIZE : -Chunk::CHUNK_SIZE * RENDER_SIZE;
			if ((*it)->IsLoad())
				(*it)->Unload();
		}
		if (abs(dif.y) > Chunk::CHUNK_SIZE * (RENDER_SIZE / 2))
		{
			(*it)->transform.position.y += dif.y > 0 ? Chunk::CHUNK_SIZE * RENDER_SIZE : -Chunk::CHUNK_SIZE * RENDER_SIZE;
			if ((*it)->IsLoad())
				(*it)->Unload();
		}
		if (abs(dif.x) > Chunk::CHUNK_SIZE * (RENDER_SIZE / 2))
		{
			(*it)->transform.position.x += dif.x > 0 ? Chunk::CHUNK_SIZE * RENDER_SIZE : -Chunk::CHUNK_SIZE * RENDER_SIZE;
			if ((*it)->IsLoad())
				(*it)->Unload();
		}
		if (!(*it)->IsLoad() && chunkUpdated < ASYNC_NUM_CHUNKS_PER_FRAME)
		{
			(*it)->UpdateMatrix();
			(*it)->SetUpChunk();
			(*it)->CreateMesh();
			chunkUpdated++;
		}
	}
	Draw();
}

void ChunkManager::FixedUpdate()
{

}
