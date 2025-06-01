#include "../include/FireBall.h"
#include "../include/ResourceManager.h"
#include "../include/Mario.h"
const float FireBall::maxDistance = 1200.0f;
const float FireBall::FB_SpeedX = 500.0f;

FireBall::FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan) :
	Entity(pos, sz, vel, dir, ON_GROUND, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), currDistance(0)
{
	this->texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("FlowerMarioFireball_RIGHT_0") :
		RESOURCE_MANAGER.getTexture("FlowerMarioFireball_LEFT_0");
	this->frameAcum = 0;
	this->currFrame = 0;
	/*this->velocity = direction == RIGHT ? Vector2{ FB_SpeedX, -500 } : Vector2{ -FB_SpeedX, -500 };*/
	this->CollNorth.setSize(Vector2{ size.x - 8, 1 });
	this->CollSouth.setSize(Vector2{ size.x - 8, 1 });
	this->CollEast.setSize(Vector2{ 1, size.y - 8 });
	this->CollWest.setSize(Vector2{ 1, size.y - 8 });
	this->updateCollision();
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
	if (velocity.x > 0)
		direction = RIGHT;
	else if (velocity.x < 0)
		direction = LEFT;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	velocity.y += GRAVITY * deltaTime;

	updateCollision();
}

void FireBall::draw()
{	
	if (isMaxDistance()) return;
	//UpdateTexture();
	DrawTexture(texture, position.x, position.y, WHITE);
}

void FireBall::updateCollision()
{
	Entity::updateCollision();
}

void FireBall::UpdateTexture()
{
	const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
	std::string textureName = "FlowerMarioFireball" + dir + std::to_string(currFrame);
	texture = RESOURCE_MANAGER.getTexture(textureName);
}

bool FireBall::isMaxDistance() const
{
	return currDistance >= maxDistance;
}

void FireBall::HandleTileCollision(const Tile tile, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) {
	case COLLISION_TYPE_EAST:
		setPosition({ tile.getX() - size.x, position.y });
		velocity.x *= -1;
		break;
	case COLLISION_TYPE_NORTH:
		setPosition({ position.x, tile.getY() + tile.getHeight() });
		velocity.y = 0;
		break;
	case COLLISION_TYPE_SOUTH:
		setPosition({ position.x, tile.getY() - size.y });
		velocity.y *= -1;
		break;
	case COLLISION_TYPE_WEST:
		setPosition({ tile.getX() + tile.getWidth(), position.y });
		velocity.x *= -1;
		break;
	default:
		break;
	}
}
