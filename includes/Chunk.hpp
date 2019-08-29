#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <iostream>
# include "Block.hpp"
# include "Renderer.hpp"

class Chunk : public Renderer
{
public: 
/*	constructors / Destructor*/	
    Chunk(); 
    Chunk(std::shared_ptr<Shader> shader, Transform transform); 
    ~Chunk(void); 
/*	public variables*/	
    static const int CHUNK_SIZE = 16;
/*	public functions*/	
    virtual void Draw() const;
	Chunk &		operator=(Chunk const & rhs);
private:
/*	private variables*/	
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    Block _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];// The blocks data
    void _CreateMeshes();
    void _CreateCube(int x, int y, int z);
/*	private functions*/	
};

#endif