#include "../include/Moon.h"

Moon::Moon(MoonType moonType, Vector2 position, Direction direction):
	PowerItem(position, {32, 32}, direction, RESOURCE_MANAGER.getTexture("Moon"))
{
	INTERVAL_JUMPING = 2.f;
	subType = 0;
}

float Moon::getPoint() const
{
	return SCORE_MOON;
}

ITEM_TYPE Moon::getItemType() const
{
	return MOON;
}