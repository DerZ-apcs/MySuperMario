#include "../include/Brick.h"

Brick::Brick(Vector2 pos, Vector2 size): 
	Blocks(pos, size)
{
}
Brick::Brick(Vector2 pos, Vector2 size, std::string textureName):
	Blocks(pos, size, textureName)
{

}
BLOCK_TYPE Brick::getBlockType() const
{
	return BRICK;
}

void Brick::breakBrick() {

}

void Brick::draw() {

}

void Brick::Update() {

}

void Brick::UpdateTexture() {

}