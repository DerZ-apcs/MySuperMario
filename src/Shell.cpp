#include "../include/Shell.h"

Shell::~Shell()
{
}

Shell::Shell(SHELL_TYPE type, Vector2 position)
{
}

ENEMY_TYPE Shell::getEnemyType() const
{
	return ENEMY_TYPE();
}

void Shell::Update()
{
}
void Shell::UpdateTexture()
{
}

void Shell::draw()
{
}

bool Shell::getIsHold() const
{
	return false;
}

void Shell::setIsHold(bool hold)
{
}

void Shell::setIsKicked(bool kicked)
{
}

bool Shell::getIsKicked() const
{
	return false;
}

void Shell::kicked(Direction direction)
{
}

void Shell::stomped(Vector2 center)
{
}

void Shell::attacked(Direction direction)
{
}

void Shell::setHoldingPosition(const Character* character)
{
}