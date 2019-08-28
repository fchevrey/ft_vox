#include "Chunk.hpp"
#include <iostream>
# include "glad.h"

Chunk::Chunk(void)
{
    return;
}
Chunk::Chunk(std::shared_ptr<Shader> shader, Transform transform) : ARenderer(shader, transform)
{
    return;
}
Chunk::~Chunk(void)
{
    glDeleteBuffers(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Chunk &	Chunk::operator=(Chunk const & rhs)
{
    return *this;
}
void Chunk::_CreateMeshes()
{
    //m_pRenderer->_CreateMesh(&m_meshID, OGLMeshType_Colour);

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if(_blocks[x][y][z].IsActive() == false)
                {
                    // Don't create triangle data for inactive blocks
                    continue;
                }

                _CreateCube(x, y, z);
            }
        }
    }
    //m_pRenderer->FinishMesh(m_meshID, -1, m_pChunkManager->GetMaterialID());
}
void	Chunk::Draw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    _shader->use();
    _shader->setMat4("view", Camera::instance->GetMatView());
    _shader->setMat4("projection", Camera::instance->GetMatProj());
    //_shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0, 5, 0)));

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void Chunk::_CreateCube(int x, int y, int z)
{
    float vert[] = {
    x - Block::RENDER_SIZE, y - Block::RENDER_SIZE, z + Block::RENDER_SIZE,
    x + Block::RENDER_SIZE, y - Block::RENDER_SIZE, z + Block::RENDER_SIZE,
    x + Block::RENDER_SIZE, y + Block::RENDER_SIZE, z + Block::RENDER_SIZE,
    x - Block::RENDER_SIZE, y + Block::RENDER_SIZE, z + Block::RENDER_SIZE,
    x + Block::RENDER_SIZE, y - Block::RENDER_SIZE, z - Block::RENDER_SIZE,
    x - Block::RENDER_SIZE, y - Block::RENDER_SIZE, z - Block::RENDER_SIZE,
    x - Block::RENDER_SIZE, y + Block::RENDER_SIZE, z - Block::RENDER_SIZE,          
    x + Block::RENDER_SIZE, y + Block::RENDER_SIZE, z - Block::RENDER_SIZE,
    };
    unsigned int indices[] ={
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        1, 4, 7,
        1, 7, 2,
        5, 0, 3,
        5, 3, 6,
        3, 2, 7,
        3, 7, 6,
        5, 4, 1,
        5, 1, 0,
    };
    glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glBindVertexArray(_vao);
	/*init vbo and copy data*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	/*init buffer for indices*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    //texture attribute
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}