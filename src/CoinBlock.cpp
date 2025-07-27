#include "../include/CoinBlock.h"
#include "../include/GameEngine.h"

CoinBlock::CoinBlock(Vector2 pos, std::string tex, int count) :
	Blocks(pos, { 32, 32 }, tex), coinCount(count), isActive(true) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
	texture = RESOURCE_MANAGER.getTexture("Brick_0");
}

//-----------------

bool CoinBlock::getActive() const {
	return isActive;
}

void CoinBlock::setActive(bool active) {
	isActive = active;
}

void CoinBlock::Activate() {
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("coin.wav");
	globalGameEngine->addEffect(new TextEffect((to_string(100)).c_str(), Vector2{ getCenterX() - size.x / 2, getTop() }));
	globalGameEngine->addEffect(new CoinEffect(Vector2{ getCenterX() - size.x / 2, getTop() - size.y }, 0.5f, 0.f));

	coinCount--;
	if (coinCount <= 0) {
		isActive = false;
		texture = RESOURCE_MANAGER.getTexture("TILE_110");
	}
}

BLOCK_TYPE CoinBlock::getBlockType() const {
	return COINBLOCK;
}

//-----------------

void CoinBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}