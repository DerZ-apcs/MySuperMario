#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "../include/PowerItem.h"

class Mushroom : public PowerItem {
private:
	MushroomType type;
public:
	//Create new mushroom
	Mushroom(MushroomType type = REDMUSHROOM, Vector2 position = { 0.f, 0.f }, Vector2 sz = {32, 32}, Direction direction = RIGHT);
	~Mushroom() = default;

	float getPoint() const override;
	//Get type of mush room
	const MushroomType& getMushroomType() const;
	ITEM_TYPE getItemType() const override;
	
};

#endif // !MUSHROOM_H