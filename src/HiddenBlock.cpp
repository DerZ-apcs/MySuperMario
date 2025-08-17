#include "../include/HiddenBlock.h"
#include "../include/GameEngine.h"

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
	revealed = false;
}

BLOCK_TYPE HiddenBlock::getBlockType() const
{
	return HIDDEN;
}

void HiddenBlock::draw()
{
	if (revealed) {
		return;
	}
	Rectangle rect = { position.x, position.y, size.x, size.y };
	// Draw the hidden block as a rectangle
	DrawRectangleLinesEx(rect, 1, GRAY);
}

void HiddenBlock::reveal()
{
	revealed = true;
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav"); 
	Blocks* newBlock = nullptr;
	switch (revealType)
	{
	case ITEMBLOCK:
		newBlock = new ItemBlock(position, size);
		break;
	case BRICK:
		newBlock = new Brick(position);
		break;
	case COINBLOCK:
		newBlock = new CoinBlock(position, size);
		break;
	default:
		newBlock = new SolidBlock(position, size);
		break;
	}
	int gridX = static_cast<int>(position.x) / 32.f;
	int gridY = static_cast<int>(position.y) / 32.f;

	auto& grid = globalGameEngine->getTileGrid();
	if (grid[gridY][gridX]) {
		delete grid[gridY][gridX];
	}
	grid[gridY][gridX] = newBlock; // Replace the block in the grid
}

void HiddenBlock::loadEntity(const json& j)
{
	Blocks::loadEntity(j);
	revealed = j["revealed"];
	revealType = static_cast<BLOCK_TYPE>(j["revealType"].get<int>());
}

void HiddenBlock::saveEntity(json& j) const
{
	Blocks::saveEntity(j);
	j["revealed"] = revealed;
	j["revealType"] = static_cast<int>(revealType);
}
