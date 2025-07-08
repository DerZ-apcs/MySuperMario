#include "../include/MovingBlock.h"

MovingBlock::MovingBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

MovingBlock::MovingBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
}

BLOCK_TYPE MovingBlock::getBlockType() const
{
	return MOVINGBLOCK;
}

void MovingBlock::draw()
{
}

void MovingBlock::setBounds(float left, float right, float top, float bottom)
{
}

Vector2 MovingBlock::getVelocity() const
{
	return Vector2();
}

void MovingBlock::setVelocity(Vector2 newVelocity)
{
}

void MovingBlock::Update()
{
}
