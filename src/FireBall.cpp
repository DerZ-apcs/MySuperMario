#include "../include/FireBall.h"
#include "../include/ResourceManager.h"

const float FireBall::maxDistance = 1000.0f;
const float FireBall::FB_SpeedX = 500.0f;

FireBall::FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan) :
	Entity(pos, sz, vel, dir, ENTITY_ACTIVE, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), currDistance(0)
{
	this->texture = direction == RIGHT ? ResourceManager::getTexture("FlowerMarioFireball_RIGHT_0") :
		ResourceManager::getTexture("FlowerMarioFireball_LEFT_0");
	this->frameAcum = 0;
	this->currFrame = 0;
}

FireBall::~FireBall() {

}

void FireBall::Update()
{
	if (isMaxDistance()) return;

	const float deltaTime = GetFrameTime();
	frameAcum += deltaTime;
	maxFrame = 3;
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame++;
		if (currFrame > maxFrame) currFrame = 0;
	}
	currDistance += abs(velocity.x) * deltaTime;

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	velocity.y += GRAVITY * deltaTime;
	if (position.y >= 550) {
		HandleGround(550);
	}
}

void FireBall::draw()
{	
	if (isMaxDistance()) return;
	//UpdateTexture();
	DrawTexture(texture, position.x, position.y, WHITE);
}

void FireBall::updateCollision()
{

}

void FireBall::UpdateTexture()
{
	const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
	std::string textureName = "FlowerMarioFireball" + dir + std::to_string(currFrame);
	texture = ResourceManager::getTexture(textureName);
}

bool FireBall::isMaxDistance() const
{
	return currDistance >= maxDistance;
}

void FireBall::HandleGround(float pos_groundY)
{
	position.y = pos_groundY - size.y;
	state = JUMPING;
	velocity.y *= -0.8;
}
