#include "../include/Luigi.h"

Luigi::Luigi(): Luigi(Vector2{32, 400}, Vector2{32, 44}, STATE_SMALL)
{
	cout << "Luigi is created" << endl;
	characterType = LUIGI;
}

Luigi::Luigi(Vector2 nposition, Vector2 nsize, CharacterState type):
	Character(nposition, nsize, type, LUIGI)
{
	MAX_WALK_SPEED_X = 400;
	MAX_RUN_SPEED_X = 580;
	MAXSPEED_Y = 580;
	ACCEL_X = 340;
	DECEL_X = 300;
	CHARACTER_GRAVITY= 720;
}

Luigi::~Luigi()
{
}

CharacterType Luigi::getCharacterType() const
{
	return LUIGI;
}

void Luigi::reset()
{
	Character::reset();
}
