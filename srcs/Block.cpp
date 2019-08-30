#include "Block.hpp"
#include <iostream>

const std::vector<unsigned int> Block::front = {
	0, 1, 2,
	2, 1, 3
};

const std::vector<unsigned int> Block::top = {
	2, 3, 4,
	4, 3, 5
};
const std::vector<unsigned int> Block::back = {
	4, 5, 6,
	6, 5, 7
};
const std::vector<unsigned int> Block::bottom = {
	6, 7, 0,
	0, 7, 1
};
const std::vector<unsigned int> Block::right = {
	1, 7, 3,
	3, 7, 5
};
const std::vector<unsigned int> Block::left = {
	6, 0, 4,
	4, 0, 2
};

Block::Block(void) : _active(true) {}
const int Block::RENDER_SIZE = 16;

Block::Block(bool active) : _active(active) {}

Block::Block(Block const & src) 
{
    *this = src;
}

Block::~Block(void)
{
    
}
Block & Block::operator=(const Block &rhs)
{
    _active = rhs._active;
    _blockType = rhs._blockType;
    return *this;
}

bool Block::IsActive() const { return _active; }

void Block::SetActive(bool active) { _active = active; }
