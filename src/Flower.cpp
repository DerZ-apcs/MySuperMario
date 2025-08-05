#include "../include/Flower.h"
#include "../include/ResourceManager.h"

Flower::Flower(FlowerType type, Vector2 position, Direction direction):
	PowerItem(position, {32, 32}, direction, RESOURCE_MANAGER.getTexture("FireFlower_0")),
	type(type)
{
	INTERVAL_JUMPING = 1.5f;
	frameAcum = 0.f;
	currFrame = 0;
	frameTime = 0.2f;
	maxFrame = 2;
}

//-----------------

const FlowerType& Flower::getFlowerType() const {
	return FIRE_FLOWER;
}

ITEM_TYPE Flower::getItemType() const {
	return FLOWER;
}

float Flower::getPoint() const
{
	return SCORE_FLOWER;
}

//-----------------

void Flower::Update() {
	PowerItem::Update();

	if (powerUpState == ACTIVE) {
		frameAcum += GetFrameTime();
		if (frameAcum >= frameTime) {
			frameAcum = 0;
			currFrame = (currFrame + 1) % maxFrame;
		}
	}
}

void Flower::UpdateTexture()
{
	if (powerUpState != ACTIVE) return;
	texture = RESOURCE_MANAGER.getTexture("FireFlower_" + std::to_string(currFrame));
}
