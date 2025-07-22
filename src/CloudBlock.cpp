#include "../include/NoteBlock.h"
#include "CloudBlock.h"

CloudBlock::CloudBlock(Vector2 pos) : Blocks(pos, { 32, 32 }, "TILE_115") {}

//-----------------

BLOCK_TYPE CloudBlock::getBlockType() const { 
	return CLOUDBLOCK;
}

//-----------------

void CloudBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}