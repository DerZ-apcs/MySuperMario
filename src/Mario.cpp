#include "../include/Mario.h"
#include "../include/Character.h"
#include <iostream>

Mario::Mario() : Mario(Vector2{ 32, 400 }, Vector2{ 32, 40 }, STATE_SMALL) {
	cout << "Mario is created" << endl;
}
	
Mario::Mario(Vector2 nposition, Vector2 nsize, CharacterState type) :
	Character(nposition, nsize, type, MARIO)
{	
	MAX_WALK_SPEED_X = 450;
	MAX_RUN_SPEED_X = 600;
	MAXSPEED_Y = 520;
	ACCEL_X = 400;
	DECEL_X = 350;
	CHARACTER_GRAVITY = 800;
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
