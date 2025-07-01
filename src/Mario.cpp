#include "../include/Mario.h"
#include <iostream>

Mario::Mario() : Mario(Vector2{ 0, 0 }, Vector2{ 32, 40 }, STATE_SMALL) {
	cout << "Mario is created" << endl;
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

void Mario::RunLeft() {
	float deltaTime = GetFrameTime();
	if (direction == RIGHT) {
		direction = LEFT;
		velocity.x = 0;
	}
	if (abs(velocity.x) + accelerationX * deltaTime >= maxspeedX) {
		velocity.x = -maxspeedX;
	}
	else {
		velocity.x -= accelerationX * deltaTime;
	}
}
void Mario::RunRight() {
	float deltaTime = GetFrameTime();
	if (direction == LEFT) {
		direction = RIGHT;
		velocity.x = 0;
	}
	if (velocity.x + accelerationX * deltaTime >= maxspeedX) {
		velocity.x = maxspeedX;
	}
	else {
		velocity.x += accelerationX * deltaTime;
	}

}
void Mario::Jumping(){
	RESOURCE_MANAGER.playSound("PLAYER_JUMP");
	velocity.y = -maxSpeedY;
	state = JUMPING;
}

void Mario::reset()
{
	Character::reset();
}
