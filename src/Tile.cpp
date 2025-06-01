#include "../include/Tile.h"

Tile::Tile(Vector2 pos, TileType type, std::string name) {
	this->position = pos;
	this->tileType = type;
	this->setSize(Vector2{ 32, 32 });
	texture = RESOURCE_MANAGER.getTexture(name);
	/*switch (tileType) {
	case TILE_TYPE_NORMAL:
		texture = ResourceManager::getTexture(name + "_NORMAL");
		break;
	case TILE_TYPE_LEFT_EDGE:
		texture = ResourceManager::getTexture(name + "_LEFT_EDGE");
		break;
	case TILE_TYPE_RIGHT_EDGE:
		texture = ResourceManager::getTexture(name + "_RIGHT_EDGE");
		break;
	}*/
}
void Tile::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}