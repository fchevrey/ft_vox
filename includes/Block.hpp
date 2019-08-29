#ifndef BLOCK_HPP
# define BLOCK_HPP

# include <iostream>
enum eBlockType
{
	Grass = 0,
	Dirt,
	Water,
	Stone,
    Wood,
    Sand,
    MAX,
};

class Block
{
public:
/*  constructors / destructor */
    Block();
    Block(const Block &rsh);
    ~Block();
/*	variables   */	
    bool IsActive();
    void SetActive(bool active);
    static const int RENDER_SIZE;
/*	functions   */	

    Block & operator=(const Block &rhs);

private:
/*	private variables   */	
    bool _active;
    eBlockType _blockType;
/*	private functions   */	
};

#endif