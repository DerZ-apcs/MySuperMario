#include "../include/Mushroom.h"
#include "../include/ResourceManager.h"

Mushroom::Mushroom(Vector2 pos) :
	PowerItem(pos, Singleton<ResourceManager>::getInstance().getTexture("MUSHROOM"), POINT) {}

//-----------------

const MushroomType& Mushroom::getMushroomType() const {
	return REDMUSHROOM; // for now only one type. to be changed later
}

EntityType Mushroom::getEntityType() const {
	return ITEM;
}

ITEM_TYPE Mushroom::getItemType() const {
	return MUSHROOM;
}

const int& Mushroom::getPoint() const {
	return POINT;
}

//-----------------
