#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Mushroom : public PowerItem {
public:
	Mushroom(Vector2 pos, Vector2 sz, Direction dir);
	~Mushroom() = default;

	const MushroomType& getMushroomType() const {
		return REDMUSHROOM;
	} // to be destroyed after merge

	void onConsume(Mario& mario) override;
};

#endif // !MUSHROOM_H