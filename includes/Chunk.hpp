#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <iostream>
# include "Block.hpp"

class Chunk 
{
public: 
/*	constructors / Destructor*/	
    Chunk(void); 
    ~Chunk(void); 
/*	public variables*/	
    static const int CHUNK_SIZE = 16;
/*	public functions*/	
    void Update(float dt);
    void Draw();
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