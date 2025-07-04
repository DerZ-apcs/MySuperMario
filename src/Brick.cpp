#include "../include/Brick.h"
#include "../include/ResourceManager.h"

Brick::Brick(Vector2 pos) : Tile(pos, TileType::TILE_TYPE_NORMAL, "TILE_104"), isBroken(false) {}

//-----------------

bool Brick::getBroken() const {
	return isBroken;
}

void Brick::setBroken(bool broken) {
	isBroken = broken;
}

//-----------------

void Brick::draw() {
	if (isBroken) { return; } // no need to draw

	Tile::draw();
}