#include "../include/Cannon.h"
#include "../include/GameEngine.h"

const float Cannon::FIRE_INTERVAL = 1.8f;

Cannon::Cannon(Vector2 pos) : Blocks(pos, { 32, 32 }, "TILE_116"), fire_time(0.0f) {
	direction = LEFT;
}

//-----------------

void Cannon::setBulletType(int type) {
	bullet_type = type;
}

void Cannon::setDirection(Direction dir) {
	direction = dir;
}

BLOCK_TYPE Cannon::getBlockType() const {
	return CANNON;
}

//-----------------

void Cannon::Update() {
	fire_time += GetFrameTime();
	std::string dir = direction == RIGHT ? "RIGHT" : "LEFT";
	if (fire_time >= FIRE_INTERVAL) {
		fire_time = 0.0f;

		float offset = (direction == Direction::LEFT) ? -32.0f : 32.0f;

		Vector2 bulletPos = { position.x + offset, position.y + 2 };
		if (bullet_type == 0) {
			Bullet* bullet = new Bullet(bulletPos, RESOURCE_MANAGER.getTexture("Bullet_" + dir), direction);
			globalGameEngine->addEnemy(bullet);
		}
		else if (bullet_type == 1) {
			FireBullet* fireBullet = new FireBullet(bulletPos, RESOURCE_MANAGER.getTexture("Bullet_" + dir), direction);
			globalGameEngine->addEnemy(fireBullet);
		}
	}
}

void Cannon::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
	fire_time = j["fire_time"];
	bullet_type = j["bullet_type"];
	direction = static_cast<Direction>(j["direction"]);
}

void Cannon::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
	j["fire_time"] = fire_time;
	j["bullet_type"] = bullet_type; // 0: Bullet, 1: FireBullet
	j["direction"] = static_cast<int>(direction);
}
