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
    Block();
    Block(const Block &rsh);
    ~Block();

    bool IsActive();
    void SetActive(bool active);
    Block & operator=(const Block &rhs);
    static const int RENDER_SIZE;


private:
/*	private variables*/	
    bool _active;
    eBlockType _blockType;
/*	private functions*/	
};

#endif