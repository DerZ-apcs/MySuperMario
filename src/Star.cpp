#include "../include/Star.h"
#include "../include/ResourceManager.h"

Star::Star(Vector2 pos) :
	PowerItem(pos, Singleton<ResourceManager>::getInstance().getTexture("STAR"), POINT) {
}

//-----------------

const StarType& Star::getStarType() const {
	return YELLOW_STAR;
}

EntityType Star::getEntityType() const {
	return ITEM;
}

ITEM_TYPE Star::getItemType() const {
	return STAR;
}

const int& Star::getPoint() const {
	return POINT;
}

//-----------------
