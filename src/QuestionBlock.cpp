#include "../include/QuestionBlock.h"
#include "../include/ResourceManager.h"
#include "../include/GameEngine.h"

QuestionBlock::QuestionBlock(Vector2 pos, ITEM_TYPE type) :
	Blocks(pos, { 32, 32 }, "QUESTION_0"), isActive(true), heldPowerUp(type) {
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

void QuestionBlock::Activate() {
	if (!isActive) return;

	texture = Singleton<ResourceManager>::getInstance().getTexture("TILE_110");
	isActive = false;

	switch (heldPowerUp) 	{
	case MUSHROOM: {
		globalGameEngine->addItem(new Mushroom(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }));
		break;
	}

	case FLOWER: {
		globalGameEngine->addItem(new Flower(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }));
		break;
	}

	case STAR: {
		globalGameEngine->addItem(new Star(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }));
		break;
	}

	default:
		break;
	}
}

BLOCK_TYPE QuestionBlock::getBlockType() const {
	return ITEMBLOCK;
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
	DrawTexture(texture, position.x, position.y, WHITE);
}