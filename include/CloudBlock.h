#ifndef CLOUD_BLOCK_H
#define CLOUD_BLOCK_H

#include <raylib.h>
#include "../include/Blocks.h"

class CloudBlock : public Blocks {
public:
	CloudBlock(Vector2 pos = {0, 0}, Vector2 size = {32, 32});
	~CloudBlock() = default;

	BLOCK_TYPE getBlockType() const override;

	void draw() override;
};

#endif // !CLOUD_BLOCK_H