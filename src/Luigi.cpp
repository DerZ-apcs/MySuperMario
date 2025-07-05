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

void Luigi::RunLeft()
{
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

void Luigi::RunRight()
{
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

void Luigi::Jumping()
{
	RESOURCE_MANAGER.playSound("PLAYER_JUMP");
	velocity.y = -maxSpeedY;
	state = JUMPING;
}

void Luigi::UpdateTexture()
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
						texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
					else
						texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_1");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SmallLuigi_LEFT_0");
					else
						texture = RESOURCE_MANAGER.getTexture("SmallLuigi_LEFT_1");
				}

			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SmallLuigi_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SmallLuigiDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SmallLuigiDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SmallLuigiJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SmallLuigiJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SmallLuigiFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SmallLuigiFalling_LEFT_0");
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
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_2");
				}

			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SuperLuigiDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SuperLuigiDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SuperLuigiJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SuperLuigiJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("SuperLuigiFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SuperLuigiFalling_LEFT_0");
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
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_0");
					else if (currFrame == 1)
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_1");
					else
						texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_2");
				}
			}
			if (velocity.x == 0 && !isducking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_0");
			}
			if (isducking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Ducking_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Ducking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Jumping_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Jumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Falling_RIGHT_0");
			else if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("Fire_Luigi_Falling_LEFT_0");
		}
		if (isThrowing) {
			if (throwFrameCounter > 0)
				throwFrameCounter--;
			else if (throwFrameCounter <= 0) {
				throwFrameCounter = 6;
				isThrowing = false;
			}
			if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("FireLuigiThrowingFireball_LEFT_0");
			else if (direction == RIGHT)
				texture = RESOURCE_MANAGER.getTexture("FireLuigiThrowingFireball_RIGHT_0");
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
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallLuigi_LEFT_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("TransitioningLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("TransitioningLuigi_LEFT_0");
			this->setSize({ 32, 56 });
			updateCollision();
		}
		else if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_0");
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
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SuperLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("SuperLuigi_LEFT_0");

		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_0");
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
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallLuigi_LEFT_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
		else if (transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("TransitioningFireLuigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("TransitioningFireLuigi_LEFT_0");
			this->setSize({ 32, 56 });
			updateCollision();
		}
		else if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("Fire_Luigi_RIGHT_0") : RESOURCE_MANAGER.getTexture("Fire_Luigi_LEFT_0");
			this->setSize({ 32, 56 });
			this->Character_state = STATE_SUPER;
			updateCollision();
		}
	}
	if (isLostLife()) {
		texture = RESOURCE_MANAGER.getTexture("SmallLuigiDying");
	}
	if (victory) {
		if (victoryFrameCounter > 0)
			victoryFrameCounter--;
		else if (victoryFrameCounter <= 0) {
			victory = false;
			exitlevel = true;
		}
		if (Character_state == STATE_SMALL)
			texture = RESOURCE_MANAGER.getTexture("SmallLuigiVictory");
		else if (Character_state == STATE_SUPER)
			texture = RESOURCE_MANAGER.getTexture("SuperLuigiVictory");
		else if (Character_state == STATE_FIRE_BALL)
			texture = RESOURCE_MANAGER.getTexture("FireLuigiVictory");
	}
}

void Luigi::reset()
{
	Character::reset();
}
