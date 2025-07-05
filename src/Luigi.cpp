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
				if (currFrame == 0)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_walk_right_0") : RESOURCE_MANAGER.getTexture("luigi_walk_left_0");
				else if (currFrame == 1)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_walk_right_1") : RESOURCE_MANAGER.getTexture("luigi_walk_left_1");

			}
			if (velocity.x == 0 && !isducking)
				texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_idle_right_0") : RESOURCE_MANAGER.getTexture("luigi_idle_left_0");
		}
		else if (state == JUMPING || state == FALLING ) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_jump_right_0") : RESOURCE_MANAGER.getTexture("luigi_jump_left_0");
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
				if (currFrame == 0) 
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_walk_right_0") : RESOURCE_MANAGER.getTexture("superluigi_walk_left_0");
				else if (currFrame == 1) 
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_walk_right_1") : RESOURCE_MANAGER.getTexture("superluigi_walk_left_1");
				else if (currFrame == 2)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_walk_right_2") : RESOURCE_MANAGER.getTexture("superluigi_walk_left_2");

			}
			if (velocity.x == 0 && !isducking) {
				texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("superluigi_idle_left_0");
			}
			if (isducking) {
				velocity.x = 0;
				texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_sit_right_0") : RESOURCE_MANAGER.getTexture("superluigi_sit_left_0");
			}
		}
		else if (state == JUMPING) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_jump_right_0") : RESOURCE_MANAGER.getTexture("superluigi_jump_left_0");
		}
		else if (state == FALLING) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_fall_right_0") : RESOURCE_MANAGER.getTexture("superluigi_fall_left_0");
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
				if (currFrame == 0)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_walk_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_walk_left_0");
				else if (currFrame == 1)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_walk_right_1") : RESOURCE_MANAGER.getTexture("fireluigi_walk_left_1");
				else if (currFrame == 2)
					texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_walk_right_2") : RESOURCE_MANAGER.getTexture("fireluigi_walk_left_2");
			}
			if (velocity.x == 0 && !isducking) {
				texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_idle_left_0");
			}
			if (isducking) {
				velocity.x = 0;
				texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_sit_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_sit_left_0");
			}
		}
		else if (state == JUMPING) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_jump_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_jump_left_0");
		}
		else if (state == FALLING) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_fall_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_fall_left_0");
		}
		if (isThrowing) {
			if (throwFrameCounter > 0)
				throwFrameCounter--;
			else if (throwFrameCounter <= 0) {
				throwFrameCounter = 6;
				isThrowing = false;
			}
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_throw_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_throw_left_0");
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
		if (transitionCurrentFrame == 0 || transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_idle_right_0") : RESOURCE_MANAGER.getTexture("luigi_idle_left_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
		else if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("superluigi_idle_left_0");
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
		if (transitionCurrentFrame == 0) 
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("superluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("superluigi_idle_right_0");
		else if (transitionCurrentFrame == 1) 
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_idle_right_0");
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
		if (transitionCurrentFrame == 2) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("fireluigi_idle_right_0") : RESOURCE_MANAGER.getTexture("fireluigi_idle_left_0");
			this->setSize({ 32, 56 });
			this->Character_state = STATE_SUPER;
			updateCollision();
		}
		else if (transitionCurrentFrame == 0 || transitionCurrentFrame == 1) {
			texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("luigi_idle_right_0") : RESOURCE_MANAGER.getTexture("luigi_idle_left_0");
			this->setSize({ 32, 40 });
			this->Character_state = STATE_SMALL;
			updateCollision();
		}
	}
	if (isLostLife()) {
		texture = RESOURCE_MANAGER.getTexture("luigi_dead_0");
	}
	if (victory) {
		if (victoryFrameCounter > 0)
			victoryFrameCounter--;
		else if (victoryFrameCounter <= 0) {
			victory = false;
			exitlevel = true;
		}
		if (Character_state == STATE_SMALL)
			texture = RESOURCE_MANAGER.getTexture("luigi_victory");
		else if (Character_state == STATE_SUPER)
			texture = RESOURCE_MANAGER.getTexture("superluigi_victory");
		else if (Character_state == STATE_FIRE_BALL)
			texture = RESOURCE_MANAGER.getTexture("fireluigi_victory");
	}
}

void Luigi::reset()
{
	Character::reset();
}
