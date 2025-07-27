#include "../include/Brick.h"
#include "../include/GameEngine.h"

Brick::Brick(Vector2 pos, Vector2 size): 
	Blocks(pos, size), isBroken(false)
{
}

Brick::Brick(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName), isBroken(false)
{
	texture = RESOURCE_MANAGER.getTexture(textureName);
}


BLOCK_TYPE Brick::getBlockType() const
{
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

void Brick::draw() {
	if (isBroken || dead) return;
	Blocks::draw();
}

void Brick::setBroken(bool broken) {
	isBroken = broken;
}

bool Brick::getBroken() const {
	return isBroken;
}