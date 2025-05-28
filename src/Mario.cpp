#include "../include/Mario.h"
#include <iostream>
#include "raymath.h"

Mario::Mario() : Mario(Vector2{ 0, 0 }, Vector2{ 32, 40 }, STATE_SMALL) {

}
	
Mario::Mario(Vector2 nposition, Vector2 nsize, MARIO_TYPE type) :
	Entity(nposition, {32, 40}, Vector2{0, 0}, RIGHT, FALLING, 0.1f, 1, WHITE),
	isDucking(false),
	Mario_State(type)
	
{
	if (type == STATE_SMALL) {
		this->size = { 32, 40 };
	}
	else  {
		this->size = { 32, 56 };
	} 
	texture = ResourceManager::getTexture("SmallMario_RIGHT_0");
	pos_onGroundY = 500;

	Mario_sprite = NORMAL;
	transitioningFrameTime = 0.06;
	transitioningFrameAcum = 0;
	transitionSteps = 11;
	transitionCurrentFrame = 0;
	transitionCurrentFramePos = 0;
	textureSprite = SMALL;
	isThrowing = false;
}

Mario::~Mario()
{
	
}
void Mario::HandleTileCollision(const Tile tile, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) {
	case COLLISION_TYPE_EAST:
		
		
		break;
	case COLLISION_TYPE_NORTH:

		break;
	case COLLISION_TYPE_SOUTH:
		setPosition({ position.x, tile.getY() - size.y });
		velocity.y = 0;
		state = ON_GROUND;
		break;
	case COLLISION_TYPE_WEST:

		break;
	default:
		break;
	}
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
	if (IsKeyPressed(KEY_SPACE) /*&& Mario_sprite == NORMAL*/) {
		TransitionMarioState();
	}
	if (IsKeyPressed(KEY_Z) && Mario_State != STATE_FIRE_BALL)
		TransitionToFire();
	if (IsKeyPressed(KEY_LEFT_CONTROL) && Mario_State == STATE_FIRE_BALL) {
		ThrowingFireBalls();
	}
	/*else isThrowing = false;*/
}

void Mario::UpdateTexture()
{
	const float deltaTime = GetFrameTime();
	switch (Mario_State) {
	case STATE_SMALL: 
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isDucking) {
				// moving
				frameTime = 0.1f;
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

		if (isThrowing) {
			if (direction == LEFT)
				texture = ResourceManager::getTexture("SuperMarioThrowingFireball_LEFT_0");
			else
				texture = ResourceManager::getTexture("SuperMarioThrowingFireball_RIGHT_0");
		
		}

		
		break;	

	case STATE_FIRE_BALL: {
			// on ground
		maxFrame = 2;
		if (state == ON_GROUND) {
			if (velocity.x != 0 && !isDucking) {
				frameAcum += deltaTime;
				if (frameAcum > frameTime) {
					currFrame++;
					if (currFrame > maxFrame) currFrame = 0;
					frameAcum -= frameTime;
				}
				if (direction == RIGHT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("Fire_Mario_RIGHT_0");
					else if (currFrame == 1)
						texture = ResourceManager::getTexture("Fire_Mario_RIGHT_1");
					else
						texture = ResourceManager::getTexture("Fire_Mario_RIGHT_2");
				}
				else if (direction == LEFT) {
					if (currFrame == 0)
						texture = ResourceManager::getTexture("Fire_Mario_LEFT_0");
					else if (currFrame == 1)
						texture = ResourceManager::getTexture("Fire_Mario_LEFT_1");
					else
						texture = ResourceManager::getTexture("Fire_Mario_LEFT_2");
				}
			}
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("Fire_Mario_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("Fire_Mario_LEFT_0");
			}
			if (isDucking) {
				velocity.x = 0;
				if (direction == RIGHT)
					texture = ResourceManager::getTexture("Fire_Mario_Ducking_RIGHT_0");
				else if (direction == LEFT)
					texture = ResourceManager::getTexture("Fire_Mario_Ducking_LEFT_0");
			}
		}
		else if (state == JUMPING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("Fire_Mario_Jumping_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("Fire_Mario_Jumping_LEFT_0");
		}
		else if (state == FALLING) {
			if (direction == RIGHT)
				texture = ResourceManager::getTexture("Fire_Mario_Falling_RIGHT_0");
			else if (direction == LEFT)
				texture = ResourceManager::getTexture("Fire_Mario_Falling_LEFT_0");
		}
		
	}
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
	this->size = { 32, 56 };
	Mario_State = STATE_SUPER;
	Mario_sprite = NORMAL;
	maxFrame = 2;
}

void Mario::TransitionToSmall()
{
	this->size = { 32, 40 };
	Mario_State = STATE_SMALL;
	Mario_sprite = NORMAL;
	maxFrame = 1;
}

void Mario::TransitionToFire()
{
	this->size = { 32, 56 };
	Mario_State = STATE_FIRE_BALL;
	maxFrame = 2;
}

void Mario::TransitionMarioState()
{
	if (Mario_State == STATE_SMALL)
		Mario_sprite = STATE_TRANSITIONING_FROM_SMALL_TO_SUPER;
	else if (Mario_State == STATE_SUPER)
		Mario_State = STATE_FIRE_BALL;
	else if (Mario_State == STATE_FIRE_BALL)
		Mario_sprite = STATE_TRANSITIONING_FROM_SUPER_TO_SMALL;
}

void Mario::ThrowingFireBalls()
{
	//isThrowing = true;
	//textureSprite = FLOWER;
	if (direction == RIGHT) {
		Vector2 velFb = Vector2Add(Vector2{400, 400}, this->velocity);
		fireballs.push_back(new FireBall(Vector2{ position.x + this->getCurrTexture().width / 2, position.y + this->getCurrTexture().height / 2 - 3 }, Vector2{ 16, 16 }, velFb, RIGHT, 2));
	}
	else if (direction == LEFT) {
		Vector2 velFb = Vector2Add(Vector2{ -400, 400 }, this->velocity);
		fireballs.push_back(new FireBall(Vector2{ position.x + this->getCurrTexture().width / 2, position.y + this->getCurrTexture().height / 2 - 3 }, Vector2{ 16, 16 }, velFb, LEFT, 2));
	}
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
	velocity.y = -maxSpeedY;
	state = JUMPING;
}

void Mario::Ducking() {
	this->isDucking = true;
}
void Mario::Standing() {
	const float deltaTime = GetFrameTime();
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
	const float deltaTime = GetFrameTime();
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
	for (auto i = fireballs.begin(); i != fireballs.end();) {
		FireBall* fireball = *i;
		if (fireball->isMaxDistance()) {
			delete fireball;
			fireball = nullptr;
			i = fireballs.erase(i);
		}
		else {
			fireball->Update();
			++i;
		}
	}
}

void Mario::draw()
{
	UpdateTexture();
	for (auto& fireball : fireballs) {
		fireball->UpdateTexture();
	}
	for (auto& fireball : fireballs) {
		fireball->draw();
	}
	if (textureSprite == SUPER)
		DrawTexture(texture, position.x, position.y - 15, WHITE);
	else if (textureSprite == TRANSITIONING)
		DrawTexture(texture, position.x, position.y - 10, WHITE);
	else DrawTexture(texture, position.x, position.y, WHITE);

	
}
