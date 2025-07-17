#include "../include/Star.h"

Star::Star(StarType type, Vector2 position, Direction direction) :
	PowerItem(position, {32, 32}, direction, YELLOW_STAR ? RESOURCE_MANAGER.getTexture("YellowStar") : RESOURCE_MANAGER.getTexture("BlueStar")),
	type(type)
{
	INTERVAL_JUMPING = 0.8f;
	
	texture = type == YELLOW_STAR ? RESOURCE_MANAGER.getTexture("YellowStar") : RESOURCE_MANAGER.getTexture("BlueStar");
}

float Star::getPoint() const
{
	return SCORE_STAR;
}

const StarType& Star::getStarType() const
{
	return type;
}

ITEM_TYPE Star::getItemType() const
{
	return STAR;
}
