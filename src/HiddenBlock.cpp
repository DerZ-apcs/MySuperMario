#include "../include/HiddenBlock.h"

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
}

BLOCK_TYPE HiddenBlock::getBlockType() const
{
	return HIDDEN;
}

void HiddenBlock::Update()
{
}

void HiddenBlock::UpdateTexture()
{
}

void HiddenBlock::draw()
{
}

void HiddenBlock::reveal()
{
}

void HiddenBlock::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
	
}

void HiddenBlock::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
}
