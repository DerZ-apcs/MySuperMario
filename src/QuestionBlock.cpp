#include "../include/QuestionBlock.h"
#include "../include/ResourceManager.h"

QuestionBlock::QuestionBlock(Vector2 pos, PowerUpType type) 
	: Tile(pos, TileType::TILE_TYPE_NORMAL, "QUESTION_0"), isActive(true), holdedPowerUp(type) {
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

void QuestionBlock::Activate(std::vector<PowerItem*>& PowerItems) {
	if (!isActive) return;

	texture = Singleton<ResourceManager>::getInstance().getTexture("TILE_110");

	isActive = false;
	switch (holdedPowerUp) 	{
	case POWERUP_MUSHROOM: {
		PowerItems.push_back(new Mushroom(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }, Vector2{ 32, 32 }, RIGHT));
		break;
	}

	case POWERUP_FLOWER: {
		PowerItems.push_back(new Flower(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }, Vector2{ 32, 32 }, RIGHT));
		break;
	}

	case POWERUP_STAR: {
		PowerItems.push_back(new Star(Vector2{ position.x + size.x / 2 - 16, position.y + size.y - 32 }, Vector2{ 32, 32 }, RIGHT));
		break;
	}

	default:
		break;
	}
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