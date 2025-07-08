#include "../include/Luigi.h"

Luigi::Luigi(): Luigi(Vector2{32, 400}, Vector2{32, 40}, STATE_SMALL)
{
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
