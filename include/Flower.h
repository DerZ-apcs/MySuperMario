#ifndef FLOWER_H
#define FLOWER_H

#include "../include/PowerItem.h"

class Flower : public PowerItem {
private:
	static constexpr int POINT = 600;

	FlowerType type;
public:
	Flower(FlowerType type = FIRE_FLOWER, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);

	~Flower();

	const FlowerType& getFlowerType() const;

	ITEM_TYPE getItemType() const override;
	float getPoint() const override;
	void Update() override;
	void UpdateTexture() override;
};

#endif // !FLOWER_H