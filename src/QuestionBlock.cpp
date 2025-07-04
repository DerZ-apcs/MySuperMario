#include "../include/QuestionBlock.h"
#include "../include/ResourceManager.h"

QuestionBlock::QuestionBlock(Vector2 pos) : Tile(pos, TileType::TILE_TYPE_NORMAL, "QUESTION_0"), isActive(true) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}

//-----------------

bool QuestionBlock::getActive() const {
	return isActive;
}

void QuestionBlock::setActive(bool active) {
	isActive = active;
}

//-----------------

void QuestionBlock::Update() {
	if (!isActive) { return; } // no need to update if not active
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;
	}

	UpdateTexture();
}

void QuestionBlock::UpdateTexture() {
	if (!isActive) { return; } // no need to update texture 

	std::string textureName = "QUESTION_" + std::to_string(currFrame);
	texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
}

void QuestionBlock::draw() {
	Tile::draw();
}