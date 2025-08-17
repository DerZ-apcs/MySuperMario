#include "../include/NoteBlock.h"
#include "../include/CloudBlock.h"

CloudBlock::CloudBlock(Vector2 pos) : Blocks(pos, { 32, 32 }, "TILE_115") {

}

//-----------------

BLOCK_TYPE CloudBlock::getBlockType() const {
	return CLOUDBLOCK;
}

//-----------------

void CloudBlock::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}

void CloudBlock::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
}

void CloudBlock::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
}
