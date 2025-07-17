#include "../include/ItemBlock.h"
#include "../include/ItemFactory.h"

ItemBlock::ItemBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size), isActive(true),
	item(COIN)
{
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}

ItemBlock::ItemBlock(Vector2 pos, Vector2 size, std::string textureName, ITEM_TYPE item):
	Blocks(pos, size, textureName), item(item), isActive(true)
{
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}


BLOCK_TYPE ItemBlock::getBlockType() const
{
	return ITEMBLOCK;
}

void ItemBlock::draw()
{
	Blocks::draw();
}

void ItemBlock::Update()
{
	if (!isActive)
		return;
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;
	}
	UpdateTexture();
}

void ItemBlock::UpdateTexture()
{
	if (!isActive) {
		texture = RESOURCE_MANAGER.getTexture("EyesClosed_0");
		return;
	}
	std::string textureName = "QUESTION_" + std::to_string(currFrame);
	texture = RESOURCE_MANAGER.getTexture(textureName);
}

void ItemBlock::releaseItem(const Entity* object)
{
	if (hasItem)
	{
	}
}

void ItemBlock::setItem(ITEM_TYPE item, int subtype)
{
}

bool ItemBlock::getActive() const
{
	return isActive;
}

void ItemBlock::setActive(bool active)
{
	this->isActive = active;
}
