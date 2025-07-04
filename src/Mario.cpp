#include "../include/Mario.h"
#include <iostream>

Mario::Mario() : Mario(Vector2{ 32, 400 }, Vector2{ 32, 40 }, STATE_SMALL) {
	/*cout << "Mario is created" << endl;*/
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
		if (velocity.x > 70 && state == ON_GROUND)
			RESOURCE_MANAGER.playSound("skid.wav");
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
		if (velocity.x < -70 && state == ON_GROUND)
			RESOURCE_MANAGER.playSound("skid.wav");
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

void Mario::UpdateTexture()
{
	const float deltaTime = GetFrameTime();
	switch (Character_state) {
	case STATE_SMALL:
		maxFrame = 1;
		frameTime = 0.1f;
		frameAcum += deltaTime;
		if (frameAcum > frameTime) {
			currFrame++;
			if (currFrame > maxFrame) currFrame = 0;
			frameAcum -= frameTime;
		}
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isducking) {
				// moving
				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
					else
						texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_1");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
					else
						texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_1");
				}

			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SmallMarioDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SmallMarioDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SmallMarioJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SmallMarioJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SmallMarioFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SmallMarioFalling_LEFT_0");
		}
		break;
	case STATE_SUPER:
		maxFrame = 2;
		frameAcum += deltaTime;
		if (frameAcum > frameTime) {
			currFrame++;
			if (currFrame > maxFrame) currFrame = 0;
			frameAcum -= frameTime;
		}
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isducking) {
				// moving

				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_2");
				}

			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SuperMarioDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SuperMarioDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SuperMarioJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SuperMarioJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SuperMarioFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SuperMarioFalling_LEFT_0");
		}
		break;

	case STATE_FIRE_BALL: {
		// on ground
		maxFrame = 2;
		frameAcum += deltaTime;
		if (frameAcum > frameTime) {
			currFrame++;
			if (currFrame > maxFrame) currFrame = 0;
			frameAcum -= frameTime;
		}
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isducking) {
				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_2");
				}
			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Ducking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Ducking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Jumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Jumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Falling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_Falling_LEFT_0");
		}
		if (isThrowing) {
			if (throwFrameCounter > 0)
				throwFrameCounter--;
			else if (throwFrameCounter <= 0) {
				throwFrameCounter = 6;
				isThrowing = false;
			}
			if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("FireMarioThrowingFireball_LEFT_0");
			else if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("FireMarioThrowingFireball_RIGHT_0");
		}
	}				
	}

	if (Character_sprite_State == STATE_TRANSITIONING_FROM_SMALL_TO_SUPER) {
		//transitionSteps = 11;
		transitioningFrameAcum += deltaTime;
		if (transitioningFrameAcum >= transitioningFrameTime) {
			transitioningFrameAcum = 0;
			transitionCurrentFramePos++;
			if (transitionCurrentFramePos <= transitionSteps) {
				transitionCurrentFrame = transitionFrameOrder[transitionCurrentFramePos];
			}
			else {
				transitionCurrentFramePos = 0;
				TransitionToSuper();
				return;
			}
		}
		if (transitionCurrentFrame == 0) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("TransitioningMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("TransitioningMario_LEFT_0");
			this->setSize({ 32, 56 });
			updateCollision();
		}
		else if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
			this->setSize({ 32, 56 });
			this->Character_state = STATE_SUPER;
			updateCollision();
		}
	}
	else if (Character_sprite_State == STATE_TRANSITIONING_FROM_SUPER_TO_FIREBALL) {
		transitioningFrameAcum += deltaTime;
		//transitionSteps--;
		if (transitioningFrameAcum >= transitioningFrameTime) {
			transitioningFrameAcum = 0;
			transitionCurrentFramePos++;
			if (transitionCurrentFramePos <= transitionSteps) {
				transitionCurrentFrame = SuperToFlowerTransitionFrameOrder[transitionCurrentFramePos];
			}
			else {
				transitionCurrentFramePos = 0;
				TransitionToFire();
				return;
			}
		}
		if (transitionCurrentFrame == 0) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");

		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0") : RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
		}

	}
	else if (Character_sprite_State == STATE_TRANSITIONING_FROM_FIREBALL_TO_SMALL) {
		transitioningFrameAcum += deltaTime;
		if (transitioningFrameAcum >= transitioningFrameTime) {
			transitioningFrameAcum = 0;
			transitionCurrentFramePos++;
			if (transitionCurrentFramePos <= transitionSteps) {
				transitionCurrentFrame = reversedTransitionFrameOrder[transitionCurrentFramePos];
			}
			else {
				transitionCurrentFramePos = 0;
				TransitionToSmall();
				return;
			}
		}
		if (transitionCurrentFrame == 0) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("TransitioningFireMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("TransitioningFireMario_LEFT_0");
			this->setSize({ 32, 56 });
			updateCollision();
		}
		else if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0") : RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
			this->setSize({ 32, 56 });
			this->Character_state = STATE_SUPER;
			updateCollision();
		}
	}
	if (isLostLife()) {
		texture = RESOURCE_MANAGER.getTexture("SmallMarioDying");
	}
	if (victory) {
		if (victoryFrameCounter > 0)
			victoryFrameCounter--;
		else if (victoryFrameCounter <= 0) {
			victory = false;
			exitlevel = true;
		}
		if (Character_state == STATE_SMALL)
			texture = RESOURCE_MANAGER.getTexture("SmallMarioVictory");
		else if (Character_state == STATE_SUPER)
			texture = RESOURCE_MANAGER.getTexture("SuperMarioVictory");
		else if (Character_state == STATE_FIRE_BALL)
			texture = RESOURCE_MANAGER.getTexture("FireMarioVictory");
	}
}

void Mario::reset()
{
	Character::reset();
}
