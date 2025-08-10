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

void TemporaryBlock::loadEntity(const json& j)
{

}

void TemporaryBlock::saveEntity(json& j) const
{
}

BLOCK_TYPE TemporaryBlock::getBlockType() const
{
	return TEMPBLOCK;
}

