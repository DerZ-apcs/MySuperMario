#include "../include/Flower.h"
#include "../include/ResourceManager.h"

Flower::Flower(Vector2 pos, Vector2 sz, Direction dir) :
	PowerItem(pos, sz, dir, Singleton<ResourceManager>::getInstance().getTexture("FLOWER_0")) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 2;
}

//-----------------

void Flower::onConsume(Mario& mario) {
	powerUpState = CONSUMED;
	//mario.TransitionToFire();
}

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
	if (powerUpState != ACTIVE) return;

	std::string textureName = "FLOWER_" + std::to_string(currFrame);
	texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
}
