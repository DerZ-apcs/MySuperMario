#ifndef BRICK_H
#define BRICK_H

#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Blocks.h" 

class Brick : public Blocks {
private:
	bool isBroken;

public:
	Brick(Vector2 pos);
	~Brick() = default;

	bool getBroken() const;
	void setBroken(bool broken);
	BLOCK_TYPE getBlockType() const override;

	void draw() override;
};

#endif // !BRICK_H
