#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <raylib.h>
#include "../include/Item.h"
#include "../include/Mario.h"

class PowerItem : public Item {
protected:
	PowerUpState powerUpState = EMERGING;

	float emergenceDis = 0.0f;
	static const float EMERGENCE_HEIGHT;
	static const float EMERGENCE_SPEED;

	static const float SPEED;

public:
	PowerItem(Vector2 pos, Texture2D tex, int point);
	~PowerItem() = default;

	PowerUpState getPowerUpState() const;

	void Update() override;
	void draw() override;

};

#endif // !POWER_ITEM_H
