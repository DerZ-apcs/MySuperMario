#ifndef DUSTEFFECT_H
#define DUSTEFFECT_H

#include "../include/Effect.h"
#include <vector>

class DustEffect : public Effect {
private:
	const float duration = 1.f;
public:
	DustEffect(Vector2 pos, float delay = 0.f);
	void Update() override;
	void draw() override;
};
#endif
