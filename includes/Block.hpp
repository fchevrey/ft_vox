#ifndef BLOCK_HPP
# define BLOCK_HPP

# include <iostream>
# include <vector>
enum eBlockType
{
	Grass = 0,
	Dirt,
	Water,
	Stone,
    Sand,
    MAX,
};

class Block
{
public:
/*  constructors / destructor */
    Block();
    Block(bool active);
    Block(const Block &rsh);
    virtual ~Block();

	static const int BLOCK_SIZE = 1;

    bool IsActive() const;
    void SetActive(bool active);

    eBlockType GetType() const;
    void SetType(eBlockType type);
/*	functions   */	

    Block & operator=(const Block &rhs);

private:
/*	private variables   */	
    bool _active;
    eBlockType _blockType;
/*	private functions   */	
};

#endif
