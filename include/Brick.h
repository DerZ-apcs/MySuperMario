#ifndef BRICK_H
#define BRICK_H

#include <raylib.h>
#include "../include/Tile.h"

class Brick : public Tile {
private:
	bool isBroken;

public:
	Brick(Vector2 pos);
	~Brick() = default;

	bool getBroken() const;
	void setBroken(bool broken);

	void draw() override;
};

#endif // !BRICK_H
