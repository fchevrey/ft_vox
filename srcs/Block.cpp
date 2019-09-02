#include "Block.hpp"
#include <iostream>

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
