#include "../include/Coin.h"
#include "../include/ResourceManager.h"

Coin::Coin(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan)
	: Entity(pos, sz, vel, dir, ON_GROUND, 0.2f, 4, YELLOW) {
	this->texture = Singleton<ResourceManager>::getInstance().getTexture("COIN_0");
	this->frameAcum = 0;
	this->currFrame = 0;

	this->CollNorth.setSize(Vector2{ size.x - 8, 1 });
	this->CollSouth.setSize(Vector2{ size.x - 8, 1 });				
	this->CollEast.setSize(Vector2{ 1, size.y - 8 });
	this->CollWest.setSize(Vector2{ 1, size.y - 8 });
	this->updateCollision();
}

//------------------

bool Coin::getCollected() const {
	return isCollected;
}

void Coin::setCollected(bool collected) {
	isCollected = collected;
}

//------------------

void Coin::Update() {
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;
	}

	UpdateTexture();
}

void Coin::UpdateTexture() {
	std::string textureName = "COIN_" + std::to_string(currFrame);
	texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
}

void Coin::draw() {
	if (isCollected) return; 
	DrawTexture(texture, position.x, position.y, WHITE);
}