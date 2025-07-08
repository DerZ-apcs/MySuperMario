#ifndef BRICK_H
#define BRICK_H

#include "../include/Blocks.h"

class Brick : public Blocks {
public:
	Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
	Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");
	BLOCK_TYPE getBlockType() const override;
	void breakBrick();
	void draw() override;
	void Update() override;
	void UpdateTexture() override;
};

#endif