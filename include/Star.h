#ifndef STAR_H
#define STAR_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Star : public PowerItem {
public:
	Star(Vector2 pos, Vector2 sz, Direction dir);
	~Star() = default;

	void onConsume(Mario& mario) override;
};

#endif // !STAR_H
