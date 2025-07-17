#ifndef BRICK_H
#define BRICK_H

#include "../include/Blocks.h"

class Brick : public Blocks {
private:
	bool isBroken;
public:
	Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
	Brick(Vector2 pos, Vector2 size, std::string textureName);
	~Brick() = default;
	BLOCK_TYPE getBlockType() const override;
	void breakBrick();
	void draw() override;
	//void Update() override;
	//void UpdateTexture() override;
	bool getBroken() const;
	void setBroken(bool broken);
};

#endif