#ifndef FIREBALL_H
#define FIREBALL_H
#include <raylib.h>
#include "../include/Entity.h"

class FireBall: public Entity {
private:
	float timeSpan;
	float timeSpanAcum;
	float maxDistance;
	float currDistance;
public:
	FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan);
	~FireBall();
	void Update() override;
	void draw() override;
	void ResolveCollision() override;
};
#endif