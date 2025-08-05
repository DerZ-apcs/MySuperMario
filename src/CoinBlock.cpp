#include "../include/CoinBlock.h"
#include "../include/GameEngine.h"

CoinBlock::CoinBlock(Vector2 pos, Vector2 size) :
	Blocks(pos, size), coinCount(1), isActive(true) {}

//-----------------

bool CoinBlock::getActive() const {
	return isActive;
}

void CoinBlock::setActive(bool active) {
	isActive = active;
}

void CoinBlock::setCount(int count) {
	this->coinCount = count;
}

void CoinBlock::Activate() {
	if (SETTING.isSoundEnabled()) 
		RESOURCE_MANAGER.playSound("coin.wav");
	globalGameEngine->addEffect(new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(100).c_str()), Vector2{ getCenterX() - size.x / 2, getTop() }));
	globalGameEngine->addEffect(new CoinEffect(Vector2{ getCenterX() - size.x / 2, getTop() - size.y }, 0.5f, 0.f));

	coinCount--;
	if (coinCount <= 0) {
		isActive = false;
		texture = Singleton<ResourceManager>::getInstance().getTexture("TILE_110");
	}
}

BLOCK_TYPE CoinBlock::getBlockType() const {
	return COINBLOCK;
}

//-----------------

void CoinBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}

void CoinBlock::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
	isActive = j["isActive"];
	coinCount = j["coinCount"];
}

void CoinBlock::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
	j["isActive"] = isActive;
	j["coinCount"] = coinCount;
}
