#ifndef FIREBALL_H
#define FIREBALL_H
#include <raylib.h>
#include "../include/Entity.h"

class FireBall: public Entity {
private:
	float timeSpan;
	float timeSpanAcum;
	static const float maxDistance;
	float currDistance;
	static const float FB_SpeedX;
public:
	FireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan);
	~FireBall();
	
	void Update() override;
	void draw() override;
	void updateCollision() override;
	void UpdateTexture() override;
	bool isMaxDistance() const;
	void HandleGround(float pos_groundY);

};
#endif