#include "../include/Mushroom.h"
#include "../include/ResourceManager.h"

Mushroom::Mushroom(MushroomType type, Vector2 position, Direction direction):
	PowerItem(position, { 32, 32 }, direction, type == GREENMUSHROOM ? RESOURCE_MANAGER.getTexture("GreenMushroom") : RESOURCE_MANAGER.getTexture("RedMushroom")),
	type(type)
{
	subType = type == GREENMUSHROOM ? 1 : 0;
	INTERVAL_JUMPING = 0.8f;
	texture = type == GREENMUSHROOM ? RESOURCE_MANAGER.getTexture("GreenMushroom") : RESOURCE_MANAGER.getTexture("RedMushroom");
}

float Mushroom::getPoint() const
{
	return SCORE_MUSHROOM;
}

const MushroomType& Mushroom::getMushroomType() const {
	return REDMUSHROOM; // for now only one type. to be changed later
}

ITEM_TYPE Mushroom::getItemType() const
{
	return MUSHROOM;
}

void Mushroom::loadEntity(const json& j)
{
	PowerItem::loadEntity(j);
	type = static_cast<MushroomType>(j["type"].get<int>());
}

void Mushroom::saveEntity(json& j) const
{
	PowerItem::saveEntity(j);
	j["type"] = static_cast<int>(type);
}
