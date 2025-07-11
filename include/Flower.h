#ifndef FLOWER_H
#define FLOWER_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Flower : public PowerItem {
public:
	Flower(Vector2 pos, Vector2 sz, Direction dir);
	~Flower() = default;

	const FlowerType& getFlowerType() const {
		return FIRE_FLOWER;
	} // to be destroyed after merge

	void onConsume(Mario& mario) override;
	void Update() override;
	void UpdateTexture() override;
};

#endif // !FLOWER_H