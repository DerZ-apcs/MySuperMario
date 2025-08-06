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

void Blocks::setId(int id) {
	this->id = id;
}

int Blocks::getId() const {
	return id;
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
	if (texture.id != 0)
	DrawTexture(texture, position.x, position.y, WHITE);
}

void Blocks::UpdateTexture()
{
}
