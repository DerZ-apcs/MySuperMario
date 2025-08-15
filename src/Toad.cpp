#include "../include/Toad.h"

Toad::Toad():
	Toad(Vector2{32, 400}, Vector2{32, 40}, STATE_SMALL)
{
	cout << "Toad is created" << endl;
}

Toad::Toad(Vector2 nposition, Vector2 nsize, CharacterState type):
	Character(nposition, nsize, type, TOAD)
{
	MAX_WALK_SPEED_X = 600;
	MAX_RUN_SPEED_X = 650;
	MAXSPEED_Y = 520;
	ACCEL_X = 450;
	DECEL_X = 400;
	CHARACTER_GRAVITY = 820;
}

Toad::~Toad()
{
}

CharacterType Toad::getCharacterType() const {
	return TOAD;
}

void Toad::draw() {
	Character::draw();
}

void Toad::reset() {
	Character::reset();
}

