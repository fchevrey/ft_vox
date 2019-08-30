#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <iostream>
# include "Block.hpp"
# include "Renderer.hpp"
# include <vector>

class Chunk : public Renderer
{
public: 
/*	constructors / Destructor*/	
    Chunk(); 
    Chunk(std::shared_ptr<Shader> shader, Transform transform); 
    virtual ~Chunk(void); 
/*	public variables*/	
    static const int CHUNK_SIZE = 16;
/*	public functions*/	
    virtual void Draw() const;
    void CreateMesh();
	void Unload();
	void SetUpChunk();
	Chunk &		operator=(Chunk const & rhs);
private:
/*	private variables*/	
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    std::vector<float>	_vertices;
	std::vector<unsigned int>	_indices;
    Block _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];// The blocks data
/*	private functions*/	
	void _CreateCube(bool lXNegative, bool lXPositive, bool lYNegative, bool lYPositive, bool lZNegative, bool lZPositive, float x, float y, float z);
    //void _CreateCube(float x, float y, float z);
    void _SendToOpenGL();
};

#endif
