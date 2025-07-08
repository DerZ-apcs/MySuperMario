#include "../include/ItemBlock.h"
#include "ItemBlock.h"

ItemBlock::ItemBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

ItemBlock::ItemBlock(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{
}

BLOCK_TYPE ItemBlock::getBlockType() const
{
	return ITEMBLOCK;
}

void ItemBlock::draw()
{
}

void ItemBlock::Update()
{
}

void ItemBlock::UpdateTexture()
{
}

void ItemBlock::releaseItem(const Entity* object)
{
}

void ItemBlock::setItem(ITEM_TYPE item, int subtype)
{
}
