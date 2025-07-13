#include "../include/Brick.h"
#include "../include/ResourceManager.h"

Brick::Brick(Vector2 pos) : Blocks(pos, { 32, 32 }, "TILE_104"), isBroken(false) {}

//-----------------

bool Brick::getBroken() const {
	return isBroken;
}

void Brick::setBroken(bool broken) {
	isBroken = broken;
	dead = true;
}

BLOCK_TYPE Brick::getBlockType() const {
	return BRICK;
}

//-----------------

void Brick::draw() {
	if (isBroken) { return; } // no need to draw

	DrawTexture(texture, position.x, position.y, WHITE);
}