#include "../include/FireBall.h"
#include "../include/ResourceManager.h"
#include "../include/Mario.h"
const float FireBall::FB_SpeedX = 300.0f;
const float FireBall::maxTime = 2.5f;

FireBall::FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan) :
	Entity(pos, sz, vel, dir, ON_GROUND, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), 
	currTime(0.f)
{
	this->texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("FlowerMarioFireball_RIGHT_0") :
		RESOURCE_MANAGER.getTexture("FlowerMarioFireball_LEFT_0");
	this->frameAcum = 0;
	this->currFrame = 0;
	this->updateCollision();
}

FireBall::~FireBall() {

}

void FireBall::Update()
{
	if (ismaxTime() || isDead()) return;
	
	const float deltaTime = GetFrameTime();
	frameAcum += deltaTime;
	maxFrame = 3;
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame++;
		if (currFrame > maxFrame) currFrame = 0;
	}
	currTime += deltaTime;
	if (velocity.x > 0)
		direction = RIGHT;
	else if (velocity.x < 0)
		direction = LEFT;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	velocity.y += GRAVITY * deltaTime;

	updateCollision();
	UpdateTexture();
}

void FireBall::draw()
{	
	updateCollision();
	if (ismaxTime() || isDead()) return;
	DrawTexture(texture, position.x, position.y, WHITE);
	if (SETTING.getDebugMode()) {
		CollNorth.draw();
		CollSouth.draw();
		CollEast.draw();
		CollWest.draw();
	}
	updateCollision();
}

void FireBall::updateCollision()
{
	//Entity::updateCollision();
	CollNorth.setPos({position.x + 4, position.y});
	CollSouth.setPos({ position.x + 4, position.y + size.y - 5 });
	CollEast.setPos({ position.x + size.x - 5, position.y + 4 });
	CollWest.setPos({ position.x, position.y + 4 });
	this->CollNorth.setSize(Vector2{ size.x - 8, 5 });
	this->CollSouth.setSize(Vector2{ size.x - 8, 5 });
	this->CollEast.setSize(Vector2{ 5, size.y - 8 });
	this->CollWest.setSize(Vector2{ 5, size.y - 8 });
}

void FireBall::UpdateTexture()
{
	updateCollision();
	const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
	std::string textureName = "FlowerMarioFireball" + dir + std::to_string(currFrame);
	texture = RESOURCE_MANAGER.getTexture(textureName);
	updateCollision();
}

bool FireBall::ismaxTime() const {
	return currTime >= maxTime;
}
float FireBall::getCurrTime() const
{
	return currTime;
}
EntityType FireBall::getEntityType() const
{
	return FIREBALL;
}

void FireBall::loadEntity(const json& j)
{
	Entity::loadEntity(j);
	timeSpan = j["timeSpan"];
	timeSpanAcum = j["timeSpanAcum"];
	currTime = j["currTime"];
}

void FireBall::saveEntity(json& j) const
{
	Entity::saveEntity(j);
	j["timeSpan"] = timeSpan;
	j["timeSpanAcum"] = timeSpanAcum;
	j["currTime"] = currTime;
}
