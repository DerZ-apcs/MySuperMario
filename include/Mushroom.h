#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "../include/Item.h"

class Mushroom : public Item {
private:
	static constexpr int POINT = 1000;
	static constexpr float SPEED = 70.f;

	MushroomType type;

	static constexpr float APPEAR_SPEED = 16.f;
public:
	//Create new mushroom
	Mushroom(MushroomType type = REDMUSHROOM, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);
	~Mushroom();

	//Get type of mush room
	const MushroomType& getMushroomType() const;
	ITEM_TYPE getItemType() const override;

	void Update() override;
	void draw() override;
	void updateCollision() override;
	void UpdateTexture() override;
	bool isMaxDistance() const;
};

#endif // !MUSHROOM_H