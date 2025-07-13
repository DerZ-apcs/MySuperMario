#ifndef FLOWER_H
#define FLOWER_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Flower : public PowerItem {
private:
	static constexpr int POINT = 150;

public:
	Flower(Vector2 pos);
	~Flower() = default;

	const FlowerType& getFlowerType() const;
	EntityType getEntityType() const override;
	ITEM_TYPE getItemType() const override;
	const int& getPoint() const;

	void Update() override;
	void UpdateTexture() override;
};

#endif // !FLOWER_H