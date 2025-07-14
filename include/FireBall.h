#ifndef FIREBALL_H
#define FIREBALL_H
#include <raylib.h>
#include "../include/Entity.h"

class FireBall: public Entity {
private:
	float timeSpan;
	float timeSpanAcum;
	static const float maxTime;
	float currTime;
	static const float FB_SpeedX;
	static const float accelerationX;
public:
	FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan);
	~FireBall();
	
	void Update() override;
	void draw() override;
	void updateCollision() override;
	void UpdateTexture() override;
	bool ismaxTime() const;
	EntityType getEntityType() const override;
};
#endif