#include "ChunkManager.hpp"

ChunkManager::ChunkManager(std::shared_ptr<Shader> shader)
{
	/*float	halfRenderSize = RENDER_SIZE / 2.0f;
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
	}*/
	std::shared_ptr<Chunk> tmp(new Chunk(shader, Transform(glm::vec3(0, 0, 0))));
	_chunkList.push_back(tmp);
}

ChunkManager::~ChunkManager() {}

void	ChunkManager::Draw()
{
	for (auto it = _chunkList.begin(); it != _chunkList.end(); it++)
		(*it)->Draw();
}

void ChunkManager::Update()
{
	for (auto it = _chunkList.begin(); it != _chunkList.end(); it++)
	{
		glm::vec3 dif = Camera::instance->GetPos() - (*it)->transform.position;
		//std::cout << dif << std::endl;
		bool changes = false;
		if (dif.z < 0 || dif.z > Chunk::CHUNK_SIZE)
		{
			(*it)->transform.position.z += dif.z > 0 ? Chunk::CHUNK_SIZE : -Chunk::CHUNK_SIZE;
			changes = true;
		}
		if (dif.y < 0 || dif.y > Chunk::CHUNK_SIZE)
		{
			(*it)->transform.position.y += dif.y > 0 ? Chunk::CHUNK_SIZE : -Chunk::CHUNK_SIZE;
			changes = true;
		}
		if (dif.x < 0 || dif.x > Chunk::CHUNK_SIZE)
		{
			(*it)->transform.position.x += dif.x > 0 ? Chunk::CHUNK_SIZE : -Chunk::CHUNK_SIZE;
			changes = true;
		}
		if (changes)
		{
			(*it)->UpdateMatrix();
			(*it)->Unload();
			(*it)->SetUpChunk();
			(*it)->CreateMesh();
		}
	}
	Draw();
}

void ChunkManager::FixedUpdate()
{

}
