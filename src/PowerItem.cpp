#include "../include/PowerItem.h"
#include "../include/ResourceManager.h"

const float PowerItem::EMERGENCE_HEIGHT = 32.0f;
const float PowerItem::EMERGENCE_SPEED = 48.0f;
const float PowerItem::SPEED = 48.0f;

//------------------

PowerItem::PowerItem(Vector2 pos, Vector2 sz, Direction dir, Texture2D tex) :
	Entity(pos, sz, Vector2{ SPEED * (dir == RIGHT ? 1.0f : -1.0f), 0 }, dir, FALLING, tex, "POWER_ITEM"), powerUpState(EMERGING)
{
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
}


//------------------

void PowerItem::setItemState(PowerUpState state) {
	powerUpState = state;
}

PowerUpState PowerItem::getItemState() const {
	return powerUpState;
}

//------------------

void PowerItem::Update() {
	if (powerUpState == CONSUMED) return;

	switch (powerUpState) {
	case ACTIVE: {
		float deltaTime = GetFrameTime();
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;

		if (state != ON_GROUND) { if (velocity.y >= 0) { state = FALLING; } }
		velocity.y += GRAVITY * deltaTime;

		break;
	}

	case EMERGING: {
		float deltaTime = GetFrameTime();
		float dy = EMERGENCE_SPEED * deltaTime;
		emergenceDis += dy; position.y -= dy;
		if (emergenceDis >= EMERGENCE_HEIGHT) {
			powerUpState = ACTIVE;
			emergenceDis = 0.0f;
		}

		break;
	}

	default: break;
	}

	updateCollision();
	UpdateTexture();
}

void PowerItem::draw() {
	if (powerUpState == CONSUMED) return;

	DrawTexture(texture, position.x, position.y, WHITE);
}