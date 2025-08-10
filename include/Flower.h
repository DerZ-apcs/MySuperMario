#ifndef FLOWER_H
#define FLOWER_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Flower : public PowerItem {
private:
	static constexpr int POINT = 600;

	FlowerType type;

	static constexpr float APPEAR_SPEED = 16.f;
public:
	Flower(FlowerType type = FIRE_FLOWER, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);
	~Flower() = default;

	const FlowerType& getFlowerType() const;
	float getPoint() const override;
	ITEM_TYPE getItemType() const override;

	void Update() override;
	void UpdateTexture() override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !FLOWER_H