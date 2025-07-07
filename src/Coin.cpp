#include "../include/Coin.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

Coin::Coin(CoinType type, Vector2 position): Item(POINT)
{
	maxFrame = 3;
	currFrame = 0;
	frameAcum = 0.f;
	frameTime = 0.1f;
	this->type = type;
	this->lifeTime = 0.f;
	texture = RESOURCE_MANAGER.getTexture("Coin_0");

	if (type == BLOCK_COIN) {
		setVelY(-COIN_UP_VELOCITY);
		setCollisionAvailable(false);
		this->lifeTime = BLOCK_COIN_LIFE_TIME;
		RESOURCE_MANAGER.playSound("coin.wav");
	}
	setPosition(position);
	setGravityAvailable(false);
}

Coin::~Coin()
{
}

EntityType Coin::getEntityType() const
{
	return ITEM;
}

const CoinType& Coin::getCoinType() const
{
	return type;
}

ITEM_TYPE Coin::getItemType() const
{
	return COIN;
}

void Coin::Update()
{
	const float deltaTime = GetFrameTime();

	Entity::Update();
	if (isDead()) return;
	if (gravityAvailable) {
		setVelY(velocity.y + GRAVITY * deltaTime);
	}
	if (type == BLOCK_COIN) {
		if (lifeTime <= 0.f) {
			setEntityDead();
			Effect* text = new TextEffect(to_string(POINT).c_str(), getCenter());
			text->setVelY(0.f);
			globalGameEngine->addEffect(text);
		}
	}
	UpdateTexture();
}

void Coin::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}

//void Coin::updateCollision()
//{
//}

void Coin::UpdateTexture()
{
	const float deltaTime = GetFrameTime();
	frameAcum += deltaTime;
	frameTime = 0.1f;
	if (frameAcum > frameTime) {
		currFrame++;
		if (currFrame > maxFrame) currFrame = 0;
		frameAcum -= frameTime;
	}
	texture = RESOURCE_MANAGER.getTexture("Coin_" + std::to_string(currFrame));
}
