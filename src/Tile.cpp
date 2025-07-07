#include "../include/Tile.h"

Tile::Tile(Vector2 pos, TileType type, std::string name) {
	this->position = pos;
	this->tileType = type;
	this->setSize(Vector2{ 32, 32 });
	texture = RESOURCE_MANAGER.getTexture(name);
}
void Tile::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}

EntityType Tile::getEntityType() const
{
	return BLOCK;
}
