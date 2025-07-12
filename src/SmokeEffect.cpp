#include "SmokeEffect.h"
#include "SmokeEffect.h"
#include "../include/SmokeEffect.h"

SmokeEffect::SmokeEffect(Vector2 pos, Vector2 vel, float delay):
	Effect(pos, delay)
{
	maxFrame = 3;
	this->position = pos;
	this->duration = duration;
	this->delayed = delay;
	this->velocity = vel;
	for (int i = 0; i < 4; i++) {
		animations.push_back(RESOURCE_MANAGER.getTexture("Puft_" + std::to_string(i)));
	}
}

void SmokeEffect::Update()
{
	const float deltaTime = GetFrameTime();
	Entity::Update();
	//if (gravityAvailable) setVelY(getVelY() + GRAVITY * deltaTime);
	setPosition({ position.x + getVelX() * deltaTime, position.y + getVelY() * deltaTime });
	velocity.y += velocity.y * deltaTime;
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

void SmokeEffect::draw()
{
	DrawTextureEx(texture, { position.x, position.y }, 0.f, 0.7f, WHITE);
}
