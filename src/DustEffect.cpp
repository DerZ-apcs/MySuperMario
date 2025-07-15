#include "../include/DustEffect.h"

DustEffect::DustEffect(Vector2 pos, float delay):
	Effect(pos, 0.f, 1.f)
{
	maxFrame = 3;
	frameTime = 0.12f;
	this->position = pos;
	this->velocity = { 0.f, 0.f };
	for (int i = 0; i < 4; i++) {
		animations.push_back(RESOURCE_MANAGER.getTexture("Dust_" + std::to_string(i)));
	}
	texture = RESOURCE_MANAGER.getTexture("Dust_0");
}

void DustEffect::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}

void DustEffect::Update()
{
	const float deltaTime = GetFrameTime();
	Entity::Update();
	frameAcum += deltaTime;
	if (frameAcum > frameTime) {
		currFrame++;
		if (currFrame >= 4) {
			setEntityDead();
			return;
		}
		frameAcum = 0;
	}
	texture = animations[currFrame];
}