#include "../include/Item.h"

Item::Item(int point)
{
	this->point = point;
	this->appear = true;
	this->bottomAppear = 0.f;
}

const int& Item::getPoint() const
{
	return this->point;
}

EntityType Item::getType() const
{
	return ITEM;
}

void Item::setAppearBottom(float bottom)
{
	this->bottomAppear = bottom;
}

const float& Item::getAppearBottom()
{
	return this->bottomAppear;
}

void Item::setAppear(bool appear)
{
	this->appear = appear;
}

bool Item::isAppear() const
{
	return this->appear;
}

void Item::Update()
{
}

void Item::draw()
{
}

void Item::updateCollision()
{
}

void Item::UpdateTexture()
{
}

void Item::HandleTileCollision(const Tile tile, CollisionType Colltype)
{
}
