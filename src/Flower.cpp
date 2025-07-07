#include "../include/Flower.h"

Flower::Flower(FlowerType type, Vector2 position, Direction direction)
{
}

Flower::~Flower()
{
}

const FlowerType& Flower::getFlowerType() const
{
	return type;
}

ITEM_TYPE Flower::getItemType() const
{
	return ITEM_TYPE();
}

void Flower::Update()
{
}

void Flower::draw()
{
}

void Flower::updateCollision()
{
}

void Flower::UpdateTexture()
{
}

void Flower::HandleTileCollision(const Tile tile, CollisionType Colltype)
{
}
