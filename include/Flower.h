#ifndef FLOWER_H
#define FLOWER_H

#include "../include/Item.h"

class Flower : public Item {
private:
	static constexpr int POINT = 1000;

	FlowerType type;

	static constexpr float APPEAR_SPEED = 16.f;
public:
	Flower(FlowerType type = FIRE_FLOWER, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);

	~Flower();

	const FlowerType& getFlowerType() const;

	ITEM_TYPE getItemType() const override;

	void Update() override;
	void draw() override;
	void updateCollision() override;
	void UpdateTexture() override;
};

#endif // !FLOWER_H