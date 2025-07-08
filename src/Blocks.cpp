#include "../include/Blocks.h"

Blocks::Blocks(Vector2 pos, Vector2 size)
{
	this->position = pos;
	this->size = size;
}
Blocks::Blocks(Vector2 pos, Vector2 size, std::string textureName)
{
	texture = RESOURCE_MANAGER.getTexture(textureName);
	this->position = pos;
	this->size = size;
}

EntityType Blocks::getEntityType() const
{
	return BLOCK;
}

void Blocks::Update()
{
}

void Blocks::draw()
{
}

void Blocks::UpdateTexture()
{
}
