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
	if (texture.id != 0)
	DrawTexture(texture, position.x, position.y, WHITE);
}

void Blocks::UpdateTexture()
{
}

void Blocks::loadEntity(const json& j)
{
	position = { j["pos"][0], j["pos"][1] };
	size = { j["size"][0], j["size"][1] };
	velocity = { j["vel"][0], j["vel"][1] };
}

void Blocks::saveEntity(json& j) const
{
	j["pos"] = { position.x, position.y };
	j["size"] = { size.x, size.y };
	j["vel"] = { velocity.x, velocity.y };
}
