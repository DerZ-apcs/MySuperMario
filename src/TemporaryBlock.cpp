#include "../include/TemporaryBlock.h"

TemporaryBlock::TemporaryBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

TemporaryBlock::TemporaryBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
}

void TemporaryBlock::Update() 
{
}

void TemporaryBlock::draw() 
{
}

BLOCK_TYPE TemporaryBlock::getBlockType() const
{
	return BLOCK_TYPE();
}

