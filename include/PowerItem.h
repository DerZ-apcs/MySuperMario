#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <raylib.h>
#include "../include/Item.h"
#include "../include/Character.h"
#include "../include/Global.h"

class PowerItem : public Item {
protected:
	PowerUpState powerUpState = EMERGING;

	float emergenceDis = 0.0f;
	static const float EMERGENCE_HEIGHT;
	static const float EMERGENCE_SPEED;

	static const float SPEED;

	const float SCORE_MUSHROOM = 200;
	const float SCORE_STAR = 300;
	const float SCORE_FLOWER = 200;
	const float SCORE_MOON = 500;

	float INTERVAL_JUMPING; // interval between jumpings
	float currtimeJumping = 0;
public:
	PowerItem(Vector2 pos, Vector2 sz, Direction dir, Texture2D tex);
	~PowerItem() = default;

	virtual float getPoint() const = 0;
	void setItemState(PowerUpState state);
	PowerUpState getPowerUpState() const;

	void Update() override;
	void draw() override;
	ITEM_TYPE getItemType() const override;
};

#endif // !POWER_ITEM_H