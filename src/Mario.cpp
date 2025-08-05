#include "../include/Mario.h"
#include "../include/Character.h"
#include <iostream>

Mario::Mario() : Mario(Vector2{ 32, 400 }, Vector2{ 32, 40 }, STATE_SMALL) {
	cout << "Mario is created" << endl;
	characterType = MARIO;
}
	
Mario::Mario(Vector2 nposition, Vector2 nsize, CharacterState type) :
	Character(nposition, nsize, type, MARIO)
{	
}

Mario::~Mario()
{
	

}
CharacterType Mario::getCharacterType() const
{
	return MARIO;
}

void Mario::reset()
{
	Character::reset();
}
