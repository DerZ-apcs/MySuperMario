#include "../include/PowerItem.h"
#include "../include/ResourceManager.h"

const float PowerItem::EMERGENCE_HEIGHT = 32.0f;
const float PowerItem::EMERGENCE_SPEED = 48.0f;
const float PowerItem::SPEED = 150.0f;

//------------------

PowerItem::PowerItem(Vector2 pos, Vector2 sz, Direction dir, Texture2D tex) :
	Item(pos, sz, Vector2{ SPEED * (dir == RIGHT ? 1.0f : -1.0f), 20 }, dir, FALLING, tex), powerUpState(EMERGING),
	INTERVAL_JUMPING(1.f)
{
	this->texture = tex;
	this->position = pos;
	this->size = { (float)texture.width, (float)texture.height };
	this->dead = false;

	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
}

//-----------------
void PowerItem::setItemState(PowerUpState state) {
	powerUpState = state;
}

//------------------

PowerUpState PowerItem::getPowerUpState() const {
	return powerUpState;
}

//------------------

void PowerItem::Update() {
	Entity::Update();
	if (isDead()) return;

	switch (powerUpState) {
	case ACTIVE: {
		gravityAvailable = true;
		collisionAvailable = true;
		float deltaTime = GetFrameTime();
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;

		currtimeJumping += deltaTime;
		if (currtimeJumping >= INTERVAL_JUMPING && state == ON_GROUND) {
			velocity.y = -300;
			state = JUMPING;
			currtimeJumping = 0.f;
		}
		if (velocity.y >= 0) 
			state = FALLING; 
		if (getGravityAvailable())
			velocity.y += GRAVITY * deltaTime;

		break;
	}

	case EMERGING: {
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("mushroom_appears.wav");
		gravityAvailable = false;
		collisionAvailable = false;
		float deltaTime = GetFrameTime();
		float dy = EMERGENCE_SPEED * deltaTime;
		emergenceDis += dy; position.y -= dy;
		if (emergenceDis >= EMERGENCE_HEIGHT) {
			powerUpState = ACTIVE;
			emergenceDis = 0.0f;

			setCollisionAvailable(true);
			setDirection(RIGHT);
			velocity = { SPEED, 0.0f };
		}

		break;
	}

	default: break;
	}

	Entity::updateCollision();
	UpdateTexture();
}

void PowerItem::draw() {
	if (isDead()) return;
	if (this->dead == true) return;

	DrawTexture(texture, position.x, position.y, WHITE);
	// debug
	if (SETTING.getDebugMode()) {
		CollNorth.draw();
		CollSouth.draw();
		CollEast.draw();
		CollWest.draw();
	}
}

ITEM_TYPE PowerItem::getItemType() const
{
	return POWERITEM;
}

void PowerItem::loadEntity(const json& j)
{
	Item::loadEntity(j);
	powerUpState = static_cast<PowerUpState>(j["powerUpState"].get<int>());
	INTERVAL_JUMPING = j["INTERVAL_JUMPING"]; // interval between jumpings
	currtimeJumping = j["currtimeJumping"];
	emergenceDis = j["emergenceDis"];
}

void PowerItem::saveEntity(json& j) const
{
	Item::saveEntity(j);
	j["powerUpState"] = static_cast<int>(powerUpState);
	j["INTERVAL_JUMPING"] = INTERVAL_JUMPING;
	j["currtimeJumping"] = currtimeJumping;
	j["emergenceDis"] = emergenceDis;
}
