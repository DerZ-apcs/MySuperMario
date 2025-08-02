#include "../include/Brick.h"
#include "../include/GameEngine.h"
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

void Brick::breakBrick() {
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("break_brick_block.wav");
	TextEffect* text = new TextEffect(to_string(20), position);
	text->setVel(Vector2{ 0, -100 });
	globalGameEngine->addEffect(text);

	isBroken = true;
	setEntityDead();
}

//-----------------

void Brick::draw() {
	if (isBroken) { return; } // no need to draw

	DrawTexture(texture, position.x, position.y, WHITE);
}