#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Mushroom : public PowerItem {
private:
	static constexpr int POINT = 150;

public:
	Mushroom(Vector2 pos);
	~Mushroom() = default;

	const MushroomType& getMushroomType() const;
	EntityType getEntityType() const override;
	ITEM_TYPE getItemType() const override;
	const int& getPoint() const;
};

#endif // !MUSHROOM_H