#ifndef STAR_H
#define STAR_H

#include <raylib.h>
#include "../include/PowerItem.h"

class Star : public PowerItem {
private:
	static constexpr int POINT = 1000;

public:
	Star(Vector2 pos);
	~Star() = default;

	const StarType& getStarType() const;
	EntityType getEntityType() const override;
	ITEM_TYPE getItemType() const override;
	const int& getPoint() const;
};

#endif // !STAR_H
