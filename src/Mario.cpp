#include "../include/Mario.h"
#include <iostream>

Mario::Mario(): 
	Mario(Vector2{100, 500}, Vector2{100, 100}, Vector2{0, 0}, STATE_SMALL, ON_GROUND, RIGHT) {}

Mario::Mario(Vector2 nposition, Vector2 nsize, Vector2 nvel, MARIO_TYPE Type0, EntityState playerState, Direction ndirection) {
	this->position = nposition;
	this->size = nsize;
	this->velocity = nvel;
	pos_onGroundY = position.y;

	Mario_sprite = NORMAL;
	Mario_State = Type0;
	state = playerState;
	this->direction = ndirection;

	maxFrame = 1;
	currFrame = 0;
	frameTime = 0.1;
	frameAcum = 0;
	isDucking = false;
	texture = ResourceManager::getTexture("SmallMario_RIGHT_0");

	transitioningFrameTime = 0.06;
	transitioningFrameAcum = 0;
	transitionSteps = 11;
	transitionCurrentFrame = 0;
	transitionCurrentFramePos = 0;
	textureSprite = SMALL;
}
Mario::~Mario()
{
	
}
void Mario::HandleInput()
{
	if (IsKeyDown(KEY_LEFT)) {
		RunLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		RunRight();
	}
	else Standing();
	if (state == ON_GROUND) {
		if (IsKeyPressed(KEY_UP)) {
			Jumping();
		}
		if (IsKeyDown(KEY_DOWN)) {
			Ducking();
		}
		else isDucking = false;
	}
	if (IsKeyPressed(KEY_SPACE) && Mario_sprite == NORMAL) {
		TransitionMarioState();
	}
}

void Mario::UpdateTexture()
{
	const float deltaTime = GetFrameTime();
	switch (Mario_State) {
	case STATE_SMALL: 
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isDucking) {
				// moving
				frameAcum += deltaTime;
				if (frameAcum > frameTime) {
					currFrame++;
					if (currFrame > maxFrame) currFrame = 0;
					frameAcum -= frameTime;
				}
				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("SmallMario_RIGHT_0");
					else
						texture = ResourceManager::getTexture("SmallMario_RIGHT_1");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("SmallMario_LEFT_0");
					else
						texture = ResourceManager::getTexture("SmallMario_LEFT_1");
				}

			}
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("SmallMario_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("SmallMario_LEFT_0");
			}
			if (isDucking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("SmallMarioDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("SmallMarioDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("SmallMarioJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("SmallMarioJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("SmallMarioFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("SmallMarioFalling_LEFT_0");
		}
		textureSprite = SMALL;
		break;
	case STATE_SUPER:
		maxFrame = 2;
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isDucking) {
				// moving
				frameAcum += deltaTime;
				if (frameAcum > frameTime) {
					currFrame++;
					if (currFrame > maxFrame) currFrame = 0;
					frameAcum -= frameTime;
				}
				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("SuperMario_RIGHT_0");
					else if (currFrame == 1)
						texture = ResourceManager::getTexture("SuperMario_RIGHT_1");
					else 
						texture = ResourceManager::getTexture("SuperMario_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("SuperMario_LEFT_0");
					else if (currFrame == 1)
						texture = ResourceManager::getTexture("SuperMario_LEFT_1");
					else 
						texture = ResourceManager::getTexture("SuperMario_LEFT_2");
				}

			}
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("SuperMario_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("SuperMario_LEFT_0");
			}
			if (isDucking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("SuperMarioDucking_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("SuperMarioDucking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("SuperMarioJumping_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("SuperMarioJumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("SuperMarioFalling_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("SuperMarioFalling_LEFT_0");
		}
		textureSprite = SUPER;
		break;	
	}

	if (Mario_sprite == STATE_TRANSITIONING_FROM_SMALL_TO_SUPER) {
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
		if (direction == RIGHT) {
			if (transitionCurrentFrame == 0) {
				texture = ResourceManager::getTexture("SmallMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = ResourceManager::getTexture("TransitioningMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = ResourceManager::getTexture("SuperMario_RIGHT_0");
		}
		else if (direction == LEFT) {
			if (transitionCurrentFrame == 0) {
				texture = ResourceManager::getTexture("SmallMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = ResourceManager::getTexture("TransitioningMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = ResourceManager::getTexture("SuperMario_LEFT_0");
		}
		textureSprite = TRANSITIONING;
	} else if (Mario_sprite == STATE_TRANSITIONING_FROM_SUPER_TO_SMALL) {
		transitioningFrameAcum += deltaTime;
		if (transitioningFrameAcum >= transitioningFrameTime) {
			transitioningFrameAcum = 0;
			transitionCurrentFramePos++;
			if (transitionCurrentFramePos <= transitionSteps) {
				transitionCurrentFrame = reversetTransitionFrameOrder[transitionCurrentFramePos];
			}
			else {
				transitionCurrentFramePos = 0;
				TransitionToSmall();
				return;
			}
		}
		if (direction == RIGHT) {
			if (transitionCurrentFrame == 0) {
				texture = ResourceManager::getTexture("SmallMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = ResourceManager::getTexture("TransitioningMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = ResourceManager::getTexture("SuperMario_RIGHT_0");
		}
		else if (direction == LEFT) {
			if (transitionCurrentFrame == 0) {
				texture = ResourceManager::getTexture("SmallMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = ResourceManager::getTexture("TransitioningMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = ResourceManager::getTexture("SuperMario_LEFT_0");
		}	
		textureSprite = TRANSITIONING;
	}
}

bool Mario::isOnGround() const
{
	return state == ON_GROUND;
}

void Mario::TransitionToSuper()
{
	Mario_State = STATE_SUPER;
	Mario_sprite = NORMAL;
}

void Mario::TransitionToSmall()
{
	Mario_State = STATE_SMALL;
	Mario_sprite = NORMAL;
}

void Mario::TransitionMarioState()
{
	if (Mario_State == STATE_SMALL)
		Mario_sprite = STATE_TRANSITIONING_FROM_SMALL_TO_SUPER;
	else if (Mario_State == STATE_SUPER)
		Mario_sprite = STATE_TRANSITIONING_FROM_SUPER_TO_SMALL;
}

void Mario::RunLeft() {
	float deltaTime = Clock::getDeltaTimeUpdate();
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
	float deltaTime = Clock::getDeltaTimeUpdate();
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
	velocity.y = -maxSpeedY;
	state = JUMPING;
}

void Mario::Ducking() {
	this->isDucking = true;
}
void Mario::Standing() {
	const float deltaTime = Clock::getDeltaTimeUpdate();
	if (velocity.x > 0) {
		velocity.x -= accelerationX * deltaTime;
	}
	else if (velocity.x < 0) {
		velocity.x += accelerationX * deltaTime;
	}
	if (abs(velocity.x) < 100) velocity.x = 0;
}

void Mario::Update()
{
	HandleInput();
	const float deltaTime = Clock::getDeltaTimeUpdate();
	if (velocity.x != 0) position.x += velocity.x * deltaTime + 0.5 * accelerationX * deltaTime * deltaTime;

	if (state != ON_GROUND) 
		if (velocity.y >= 0) 
			state = FALLING;
	position.y += velocity.y * deltaTime;
	if (position.y + 0.5 * GRAVITY * deltaTime * deltaTime >= pos_onGroundY) {
		position.y = pos_onGroundY;
		velocity.y = 0;
		state = ON_GROUND;
		//Standing();
	}
	else {
		velocity.y += GRAVITY * deltaTime;
		position.y += 0.5 * GRAVITY * deltaTime * deltaTime;
	}
}

void Mario::draw()
{
	UpdateTexture();
	
	if (textureSprite == SUPER)
		DrawTexture(texture, position.x, position.y - 15, WHITE);
	else if (textureSprite == TRANSITIONING)
		DrawTexture(texture, position.x, position.y - 10, WHITE);
	else DrawTexture(texture, position.x, position.y, WHITE);
}

