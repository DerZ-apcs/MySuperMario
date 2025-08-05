#include "../include/Item.h"

Item::Item(int point)
{
	this->point = point;
}

Item::Item(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex):
	Entity(pos, sz, vel, dir, state, tex, "")
{
}

const int& Item::getPoint() const
{
	return this->point;
}

EntityType Item::getEntityType() const
{
	return ITEM;
}

void Item::Update()
{
}

void Item::draw()
{
}

void Item::updateCollision()
{
	Entity::updateCollision();
}

void Item::UpdateTexture()
{
}

void Item::loadEntity(const json& j)
{
	Entity::loadEntity(j);
	point = j["point"];
}

void Item::saveEntity(json& j) const
{
	Entity::saveEntity(j);
	j["point"] = point;
}
