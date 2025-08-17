#include "../include/SolidBlock.h"

SolidBlock::SolidBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
}

BLOCK_TYPE SolidBlock::getBlockType() const {
    return SOLIDBLOCK;
}

void SolidBlock::Update() {
    // No behavior for solid blocks
}

void SolidBlock::draw() {
    DrawTexture(texture, position.x, position.y, WHITE);
}