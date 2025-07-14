#include "../include/Mushroom.h"

Mushroom::Mushroom(MushroomType type, Vector2 position, Direction direction)
{
}

Mushroom::~Mushroom()
{
}

const MushroomType& Mushroom::getMushroomType() const
{
	return type;
}

ITEM_TYPE Mushroom::getItemType() const
{
	return ITEM_TYPE();
}

void Mushroom::Update()
{
}

void Mushroom::draw()
{
}

void Mushroom::updateCollision()
{
}

void Mushroom::UpdateTexture()
{
}

bool Mushroom::isMaxDistance() const
{
	return false;
}