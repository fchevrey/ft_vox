#include "Block.hpp"
#include <iostream>

const int Block::RENDER_SIZE = 16;

Block::Block(void)
{
    return;
}

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