#ifndef BRICK_H
#define BRICK_H

#include <raylib.h>
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

	void breakBrick();

	void draw() override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !BRICK_H
