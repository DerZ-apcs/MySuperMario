#include "../include/DecorBlock.h"

DecorBlock::DecorBlock(Vector2 pos, Vector2 size) :
	Blocks(pos, size)
{
	setCollisionAvailable(false);
}

DecorBlock::DecorBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
	setCollisionAvailable(false);
}

//---------------	

BLOCK_TYPE DecorBlock::getBlockType() const
{
	return DECOR;
}

//---------------

void DecorBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}

