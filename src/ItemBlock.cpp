#include "../include/ItemBlock.h"
#include "../include/ItemFactory.h"
#include "../include/GameEngine.h"
#include <random>

static Direction getRandomDirection() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dist(0, 1);

	return dist(gen) == 0 ? Direction::LEFT : Direction::RIGHT;
}
ItemBlock::ItemBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size), isActive(true), heldPowerUp(MUSHROOM),
	subType(0)
{
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}

ItemBlock::ItemBlock(Vector2 pos, ITEM_TYPE type, int subType):
	Blocks(pos, {32, 32}, "QUESTION_0"), isActive(true),
	heldPowerUp(type), subType(subType)
{
	
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}


BLOCK_TYPE ItemBlock::getBlockType() const
{
	return ITEMBLOCK;
}

void ItemBlock::setItem(ITEM_TYPE type, int subType)
{
	this->heldPowerUp = type;
	this->subType = subType;
}

void ItemBlock::draw()
{
	Blocks::draw();
}

void ItemBlock::Update()
{
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;
	}
	UpdateTexture();
}

void ItemBlock::UpdateTexture()
{
	if (!isActive) {
		texture = RESOURCE_MANAGER.getTexture("TILE_110");
		return;
	}
	texture = RESOURCE_MANAGER.getTexture("QUESTION_" + std::to_string(currFrame));
}

bool ItemBlock::getActive() const
{
	return isActive;
}

void ItemBlock::setActive(bool active)
{
	this->isActive = active;
}

void ItemBlock::Activate()
{
	if (!isActive) return;
	texture = RESOURCE_MANAGER.getTexture("EyesClosed_0");
	isActive = false;

	ItemFactory& factory = ItemFactory::getInstance();
	Item* item = factory.createItem(heldPowerUp, { position.x, position.y}, getRandomDirection(), subType);
	globalGameEngine->addItem(item);
}

void ItemBlock::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
	isActive = j["isActive"];
	heldPowerUp = static_cast<ITEM_TYPE>(j["heldPowerUp"].get<int>());
	subType = j["subType"];
}

void ItemBlock::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
	j["isActive"] = isActive;
	j["heldPowerUp"] = static_cast<int>(heldPowerUp);
	j["subType"] = subType;
}
