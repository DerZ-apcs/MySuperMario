#include "../include/Blocks.h"

Blocks::Blocks(Vector2 pos, Vector2 size)
{
	this->position = pos;
	this->size = size;
}
Blocks::Blocks(Vector2 pos, Vector2 size, std::string textureName)
{
	nameTexture = textureName;
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

void Blocks::loadEntity(const json& j)
{
	position = { j["pos"][0], j["pos"][1] };
	nameTexture = j["nameTexture"];
	id = j["id"];
}

void Blocks::saveEntity(json& j) const
{
	j["pos"] = {position.x, position.y};
	j["nameTexture"] = nameTexture;
	j["id"] = id;
}

void Blocks::setTextureName(std::string name)
{
	this->nameTexture = name;
}

std::string Blocks::getTextureName() const
{
	return nameTexture;
}
