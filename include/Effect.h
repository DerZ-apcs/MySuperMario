#ifndef EFFECT_H
#define EFFECT_H

#include "../include/Entity.h"

class Effect : public Entity {
protected:
	float timespan;
	float timespanAcum;
	float duration;
	float delayed;
	bool destroyWhenFinish;
	std::vector<Texture2D> animations;
public:
	virtual ~Effect();
	Effect() = default;
	Effect(Vector2 pos = {0.f, 0.f}, float delay = 0.f, float duration = 0.f);

	Effect(Vector2 position = { 0.f, 0.f }, bool destroyWhenFinish = true, float delay = 0.f, float duration = 0.f);

	Effect(Vector2 pos, float duration, std::vector<Texture2D> animations, float delay);
	EntityType getEntityType() const override;

	virtual void Update() override;
	virtual void draw() override;
};
#endif