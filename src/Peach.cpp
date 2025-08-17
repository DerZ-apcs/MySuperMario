#include "../include/Peach.h"
#include "../include/Character.h"

#include <iostream>

Peach::Peach() : 
	Peach(Vector2{ 32, 400 }, Vector2{ 26, 46 }, STATE_SMALL) {
	std::cout << "Peach is created" << std::endl;
	characterType = PEACH;

}

Peach::Peach(Vector2 nposition, Vector2 nsize, CharacterState type) :
	Character(nposition, nsize, type, PEACH)
{
	MAX_WALK_SPEED_X = 420;
	MAX_RUN_SPEED_X = 560;
	MAXSPEED_Y = 480;
	ACCEL_X = 380;
	DECEL_X = 340;
	CHARACTER_GRAVITY = 650;
}

Peach::~Peach()
{
	std::cout << "Peach is destroyed" << std::endl;
}

CharacterType Peach::getCharacterType() const
{
	return PEACH;
}

void Peach::draw() {
	Character::draw();
}
void Peach::reset() {
	Character::reset();
}