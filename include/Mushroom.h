#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Mushroom : public PowerItem {
private:
	MushroomType type;
public:
	//Create new mushroom
	Mushroom(MushroomType type = REDMUSHROOM, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);
	~Mushroom() = default;

	float getPoint() const override;
	//Get type of mush room
	const MushroomType& getMushroomType() const;
	ITEM_TYPE getItemType() const override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !MUSHROOM_H