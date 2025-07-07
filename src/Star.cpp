#include "../include/Star.h"

Star::Star(StarType type, Vector2 position, Direction direction)
{
}

const StarType& Star::getStarType() const
{
	return type;
}

void Star::Update()
{
}

void Star::draw()
{
}

void Star::updateCollision()
{
}

void Star::UpdateTexture()
{
}

void Star::HandleTileCollision(const Tile tile, CollisionType Colltype)
{
}

ITEM_TYPE Star::getItemType() const
{
	return STAR;
}
