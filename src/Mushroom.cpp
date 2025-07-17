#include "../include/Mushroom.h"

Mushroom::Mushroom(MushroomType type, Vector2 position, Direction direction):
	PowerItem(position, { 32, 32 }, direction, type == GREENMUSHROOM ? RESOURCE_MANAGER.getTexture("GreenMushroom") : RESOURCE_MANAGER.getTexture("RedMushroom")),
	type(type)
{
	INTERVAL_JUMPING = 0.8f;
	texture = type == GREENMUSHROOM ? RESOURCE_MANAGER.getTexture("GreenMushroom") : RESOURCE_MANAGER.getTexture("RedMushroom");
}

float Mushroom::getPoint() const
{
	return SCORE_MUSHROOM;
}

const MushroomType& Mushroom::getMushroomType() const
{
	return type;
}

ITEM_TYPE Mushroom::getItemType() const
{
	return MUSHROOM;
}
