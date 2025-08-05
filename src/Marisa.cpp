#include "../include/Marisa.h"
#include "../include/Character.h"

#include <iostream>

Marisa::Marisa() : Marisa(Vector2{ 32, 400 }, Vector2{ 37, 54 }, STATE_SMALL) {
	std::cout << "Marisa is created" << std::endl;
	characterType = MARISA;
}

Marisa::Marisa(Vector2 nposition, Vector2 nsize, CharacterState type) :
	Character(nposition, nsize, type, MARISA)
{
}

Marisa::~Marisa()
{
	std::cout << "Marisa is destroyed" << std::endl;
}

CharacterType Marisa::getCharacterType() const
{
	return MARISA;
}

void Marisa::draw() {
	Character::draw();
}
void Marisa::reset() {
	Character::reset();
}
void Marisa::UpdateTexture() {
	frameTime = 0.2f;
	std::string charactertype = "Marisa";
	std::string characterDir = getDir() == RIGHT ? "_RIGHT_" : "_LEFT_";
	std::string characterState;

	if (Character_state == STATE_SMALL || Character_state == STATE_STAR)
		characterState = "Small";
	else if (Character_state == STATE_SUPER || Character_state == STATE_SUPERSTAR)
		characterState = "Super";
	else if (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR)
		characterState = "Fire";
	maxFrame = 1;

	const float deltaTime = GetFrameTime();
	frameTime = 0.1f;
	frameAcum += deltaTime;
	if (frameAcum > frameTime) {
		currFrame++;
		if (currFrame > maxFrame) currFrame = 0;
		frameAcum -= frameTime;
	}
	if (state == ON_GROUND || state == SINKING) {
		if (velocity.x != 0 && !isducking)
			// moving
			//if (getCharacterType() != MARISA)
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + characterDir + std::to_string(currFrame + 1));
		if (velocity.x == 0 && !isducking)
			// idling
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + characterDir + "0");
	}
	else if (state == JUMPING)
		texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "Jumping" + characterDir + "0");
	else if (state == FALLING)
		texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "Falling" + characterDir + "0");

	// dying
	if (isLostLife())
		texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "Dying");
	// victory
	if (victory) {
		if (victoryFrameCounter > 0)
			victoryFrameCounter--;
		else if (victoryFrameCounter <= 0) {
			victory = false;
			exitlevel = true;
		}
		texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "Victory");
	}
	// throwing
	if (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR) {
		if (isThrowing) {
			if (throwFrameCounter > 0)
				throwFrameCounter--;
			else if (throwFrameCounter <= 0) {
				throwFrameCounter = 6;
				isThrowing = false;
			}
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "ThrowingFireball" + characterDir + "0");
		}
	}

	Character::UpdateTransitioningTexture();
}

//void Marisa::updateCollision {
//
//}