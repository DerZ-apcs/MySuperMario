#include "../include/Coin.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"
#include "../include/ResourceManager.h"

Coin::Coin(CoinType type, Vector2 pos)
	: Item(POINT), coinType(type) {
	this->texture = RESOURCE_MANAGER.getTexture("COIN_0");
	this->position = pos;
	this->size = { (float)texture.width, (float)texture.height };
	this->dead = false;

	this->maxFrame = 4;
	this->currFrame = 0;
	this->frameTime = 0.15f;
	this->frameAcum = 0.0f;

	setGravityAvailable(false);
	setCollisionAvailable(true);
	Entity::updateCollision();
	}

//------------------

const int& Coin::getPoint() const {
	return POINT;
}

ITEM_TYPE Coin::getItemType() const {
	return COIN;
}

EntityType Coin::getEntityType() const {
	return ITEM;
}

const CoinType& Coin::getCoinType() const
{
	return STATIC_COIN;
}

//------------------

void Coin::Update() {

	if (this->dead == true) return; 

	//printf("Coin Update\n");
	Entity::Update();
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;
	}

	UpdateTexture();
	Entity::updateCollision();
}

void Coin::UpdateTexture() {
	std::string textureName = "COIN_" + std::to_string(currFrame);
	texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
}

void Coin::draw() {
	if (this->dead == true) return; 
	DrawTexture(texture, position.x, position.y, WHITE);
}
