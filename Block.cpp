#include "Block.h"


void Block::changeBlockType(BlockType blockType)
{
	blocktype = blockType;
}

Block::Block()
{
	blocktype = BlockType::BlockType_Air;
	isVisible = false;
}

