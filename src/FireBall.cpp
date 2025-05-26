#include "../include/FireBall.h"
#include "../include/ResourceManager.h"


FireBall::FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan):
	Entity(pos, sz, vel, dir, ENTITY_ACTIVE, 0.05, 4), timeSpan(timeSpan), timeSpanAcum(0), maxDistance(500), currDistance(0)
{ }

FireBall::~FireBall() = default;

void FireBall::Update()
{
	const float deltaTime = getFrameTime();
	frameAcum += deltaTime;
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame++;
		currFrame %= maxFrame;
	}
	if (state != ENTITY_TO_BE_REMOVED) {
		timeSpanAcum += deltaTime;
		if (timeSpanAcum > timeSpan) {
			state = ENTITY_TO_BE_REMOVED;
		}
	}
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	velocity.y += GRAVITY;

}

void FireBall::draw()
{
	const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
	
	std::string textureName = "FlowerMarioFireball" + dir + std::to_string(currFrame);
	DrawTexture(ResourceManager::getTexture(textureName), position.x, position.y, WHITE);
}

void FireBall::ResolveCollision()
{
}

