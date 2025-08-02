#ifndef SMOKEEFFECT_H
#define SMOKEEFFECT_H

#include "../include/Effect.h"
#include <vector>

class SmokeEffect : public Effect {
private:
	const float smoke_velX = 50.f;
	const float smoke_speed = 100.f;
public:
	SmokeEffect(Vector2 pos, Vector2 vel, float delay = 0.f);
	void Update() override;
	void draw() override;
}; 
#endif