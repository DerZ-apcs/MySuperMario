#include "../include/Flower.h"
#include "../include/ResourceManager.h"

Flower::Flower(Vector2 pos) :
	PowerItem(pos, Singleton<ResourceManager>::getInstance().getTexture("FLOWER_0"), POINT) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 2;
}

//-----------------

const FlowerType& Flower::getFlowerType() const {
	return FIRE_FLOWER;
}

EntityType Flower::getEntityType() const {
	return ITEM;
}

ITEM_TYPE Flower::getItemType() const {
	return FLOWER;
}

const int& Flower::getPoint() const {
	return POINT;
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

void Flower::UpdateTexture() {
	if (this->dead == true) return;

	std::string textureName = "FLOWER_" + std::to_string(currFrame);
	texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
}
