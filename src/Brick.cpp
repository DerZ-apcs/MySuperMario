#include "../include/Brick.h"
#include "../include/GameEngine.h"
#include <ScoreEffect.h>

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
	ScoreEffect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(20).c_str()), position);
	score->setVel(Vector2{ 0, -50 });
	globalGameEngine->addEffect(score);

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