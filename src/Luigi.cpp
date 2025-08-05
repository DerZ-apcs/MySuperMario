#include "../include/Luigi.h"

Luigi::Luigi(): Luigi(Vector2{32, 400}, Vector2{32, 44}, STATE_SMALL)
{
	cout << "Luigi is created" << endl;
	characterType = LUIGI;
}

Luigi::Luigi(Vector2 nposition, Vector2 nsize, CharacterState type):
	Character(nposition, nsize, type, LUIGI)
{
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
