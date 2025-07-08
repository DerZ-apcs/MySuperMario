#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <raylib.h>
#include "../include/Entity.h"
#include "../include/EntityState.h"
#include "../include/Mario.h"

class PowerItem : public Entity {
protected:
	PowerUpState powerUpState;

	float emergenceDis = 0.0f;
	static const float EMERGENCE_HEIGHT;
	static const float EMERGENCE_SPEED;

	static const float SPEED;

public:
	PowerItem(Vector2 pos, Vector2 sz, Direction dir, Texture2D tex);
	~PowerItem() = default;

	void setItemState(PowerUpState state);
	PowerUpState getItemState() const;
	virtual void onConsume(Mario& mario) = 0;

	void Update() override;
	void draw() override;

};

#endif // !POWER_ITEM_H
