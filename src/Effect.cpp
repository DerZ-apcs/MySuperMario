#include "../include/Effect.h"
#include <iostream>

Effect::~Effect()
{
	
}

Effect::Effect(Vector2 pos, float delay, float duration)
{
	this->position = pos;
	this->duration = duration;
	this->delayed = delay;
	this->destroyWhenFinish = true;
	setCollisionAvailable(false);
	setGravityAvailable(true);
	timespan = 0.1f;
	timespanAcum = 0.f;
}

Effect::Effect(Vector2 position, bool destroyWhenFinish, float delay, float duration)
{
	this->position = position;
	timespan = 0.1f;
	timespanAcum = 0.f;
	this->duration = duration;
	this->delayed = delay;
	this->destroyWhenFinish = destroyWhenFinish;
	setCollisionAvailable(false);
	setGravityAvailable(true);
}

Effect::Effect(Vector2 pos, float duration, std::vector<Texture2D> animations, float delay)
{
	this->position = pos;
	this->duration = duration;
	if (!animations.empty()) this->texture = animations[0];
	this->delayed = delay;
	this->destroyWhenFinish = destroyWhenFinish;
	setCollisionAvailable(false);
	setGravityAvailable(true);
	maxFrame = animations.size() - 1;
	this->animations = animations;
}

EntityType Effect::getEntityType() const
{
	return EFFECT;
}

void Effect::Update()
{
	const float deltaTime = GetFrameTime();
	Entity::Update();
	if (duration <= 0.f) setEntityDead();
	if (gravityAvailable) setVelY(getVelY() + GRAVITY * deltaTime);
	//std::cout << "velo y: " << velocity.y << endl;
	duration -= deltaTime;

	if (maxFrame > 0) {
		frameAcum += deltaTime;
		if (frameAcum > frameTime) {
			currFrame++;
			if (currFrame > maxFrame) currFrame = 0;
			frameAcum = 0;
		}
		texture = animations[currFrame];
	}	
}

void Effect::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}
