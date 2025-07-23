#include "../include/RotatingBlock.h"
#include "../include/ResourceManager.h"


const float RotatingBlock::ROTATION_PERIOD = 1.6f; // seconds

//-----------------

RotatingBlock::RotatingBlock(Vector2 pos) :
	Blocks(pos, { 32, 32 }, "ROTATING_0"), isActive(false), rotatingTime(0.0f) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.05f;
	this->maxFrame = 4;
}

//-----------------

bool RotatingBlock::getActive() const {
	return isActive;
}

void RotatingBlock::setActive(bool active) {
	isActive = active;
}

void RotatingBlock::Activate() {
	if (isActive) return;

	isActive = true;
	rotatingTime = 0.0f; 
}

BLOCK_TYPE RotatingBlock::getBlockType() const {
	return ROTATINGBLOCK;
}

//-----------------

void RotatingBlock::Update() {
	if (!isActive) return;

	rotatingTime += GetFrameTime();
	UpdateTexture();
}

void RotatingBlock::UpdateTexture() {
	if (rotatingTime >= ROTATION_PERIOD) {
		rotatingTime = 0.0f; // Reset 
		isActive = false;
		texture = Singleton<ResourceManager>::getInstance().getTexture("ROTATING_0");
		return; 
	}

	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;

		std::string textureName = "ROTATING_" + std::to_string(currFrame);
		texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
	}
}

void RotatingBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}