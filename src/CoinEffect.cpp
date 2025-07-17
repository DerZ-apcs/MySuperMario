#include "../include/CoinEffect.h"

CoinEffect::CoinEffect(Vector2 pos, float duration, float delay):
	Effect(pos, delay, duration)
{
	this->texture = RESOURCE_MANAGER.getTexture("COIN_0");
	setSize({ 32.f, 32.f });
	setVel({ 0.f, -350.f });

	this->animations.push_back(Singleton<ResourceManager>::getInstance().getTexture("COIN_0"));
	this->animations.push_back(Singleton<ResourceManager>::getInstance().getTexture("COIN_1"));
	this->animations.push_back(Singleton<ResourceManager>::getInstance().getTexture("COIN_2"));
	this->animations.push_back(Singleton<ResourceManager>::getInstance().getTexture("COIN_3"));
	this->currFrame = 0;
	this->maxFrame = 4;
}

CoinEffect::CoinEffect(Vector2 pos, std::vector<Texture2D> animations, float duration, float delay):
	Effect(pos, duration, animations, delay)
{
	if (!animations.empty()) this->texture = animations[0];
	setSize({ 32.f, 32.f });
	setVel({ 0.f, -200.f });
}

//----------------------------

void CoinEffect::Update() {
	const float deltaTime = GetFrameTime();
	setPosition({ position.x, getPosition().y + getVelY() * deltaTime });
	velocity.y += GRAVITY * deltaTime;

	UpdateTexture();
	Entity::Update();
	duration -= deltaTime;
	if (duration <= 0.f) setEntityDead();
}

void CoinEffect::UpdateTexture() {
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;

		std::string textureName = "COIN_" + std::to_string(currFrame);
		texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
	}
}

void CoinEffect::draw() {
	if (this->dead == true) return;
	DrawTexture(texture, position.x, position.y, WHITE);
}