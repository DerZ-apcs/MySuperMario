#ifndef CANNON_H
#define CANNON_H

#include <raylib.h>
#include "../include/Blocks.h"
#include "../include/Bullet.h"

class Cannon : public Blocks {
private:
	float fire_time;
	static const float FIRE_INTERVAL; 

	int bullet_type = 0; // 0: Bullet, 1: FireBullet
	Direction direction = Direction::LEFT; 

public:
	Cannon(Vector2 pos);
	~Cannon() = default;

	void setBulletType(int type);
	void setDirection(Direction dir);

	BLOCK_TYPE getBlockType() const override;

	void Update() override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !CANNON_H
