#include "../include/Floor.h"

Floor::Floor(Vector2 pos, Vector2 size) :
	Blocks(pos, size)
{
}

Floor::Floor(Vector2 pos, Vector2 size, std::string texturename):
	Blocks(pos, size, texturename)
{
}

BLOCK_TYPE Floor::getBlockType() const
{
	return FLOOR;
}

void Floor::Update()
{
	// static floor has no update
}

void Floor::draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}
