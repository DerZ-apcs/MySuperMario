#ifndef FLOOR_H
#define FLOOR_H

#include "../include/Blocks.h"

class Floor : public Blocks {
public:
	Floor(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
	//Floor(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string texturename = "TILE_0");
	BLOCK_TYPE getBlockType() const override;
	void Update() override;
	void draw() override;
};
#endif