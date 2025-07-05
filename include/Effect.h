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
public:
	virtual ~Effect();
	Effect() = default;
	Effect(Vector2 pos, Vector2 size, float delay = 0.f, float timespan);

	Effect(Vector2 position = { 0.f, 0.f }, bool destroyWhenFinish = true, float delay = 0.f, float timespan);

	virtual EntityType getType() const;

	virtual void Update() override;
	virtual void draw() override;
	virtual void UpdateTexture() override;
};
#endif