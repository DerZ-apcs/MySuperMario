#include "../include/DecorBlock.h"

DecorBlock::DecorBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

DecorBlock::DecorBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
}

void DecorBlock::draw()
{
}

void DecorBlock::Update()
{
	// no update for decor
}

BLOCK_TYPE DecorBlock::getBlockType() const
{
	return DECOR;
}

