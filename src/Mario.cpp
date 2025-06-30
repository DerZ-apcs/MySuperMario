#include "../include/Mario.h"
#include <iostream>
#include "raymath.h"

Mario::Mario() : Mario(Vector2{ 0, 0 }, Vector2{ 32, 40 }, STATE_SMALL) {
	cout << "Mario is created" << endl;
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

	texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
	Mario_sprite = NORMAL;
	LastStateb4Transition = NORMAL;
	transitioningFrameTime = 0.06;
	transitioningFrameAcum = 0;
	transitionSteps = 11;
	transitionCurrentFrame = 0;
	transitionCurrentFramePos = 0;
	isThrowing = false;

	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	CollNorth.setColor(RED);
	CollSouth.setColor(GREEN);
	CollWest.setColor(BLUE);
	CollEast.setColor(BLACK);
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
		setPosition({tile.getX() - size.x, position.y});
		velocity.x = 0;
		break;
	case COLLISION_TYPE_NORTH:
		setPosition({position.x, tile.getY() + tile.getHeight()});
		velocity.y = 0;
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		setPosition({ position.x, tile.getY() - size.y });
		velocity.y = 0;
		state = ON_GROUND;
		break;
	case COLLISION_TYPE_WEST:
		setPosition({tile.getX() + tile.getWidth(), position.y});
		velocity.x = 0;
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
	if (IsKeyPressed(KEY_SPACE)) {
		TransitionMarioState();
	}
	if (IsKeyPressed(KEY_Z) && Mario_State != STATE_FIRE_BALL)
		TransitionToFire();
	if (IsKeyPressed(KEY_LEFT_CONTROL) && Mario_State == STATE_FIRE_BALL) {
		ThrowingFireBalls();
	}
}

void Mario::updateCollision()
{
	if (isDucking){
		CollNorth.setPos({position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + size.y / 2 - CollNorth.getHeight()});
		CollEast.setSize({ 5, size.y / 2 });
		CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + size.y * 3 / 4 - CollEast.getHeight() / 2});
		CollWest.setSize({ 5, size.y / 2 });
		CollWest.setPos({ position.x , position.y + size.y * 3 / 4 - CollWest.getHeight() / 2 });
	}
	else {
		CollWest.setSize({ 5, size.y - 5 });
		CollEast.setSize({ 5, size.y - 5 });
		Entity::updateCollision();
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
				frameTime = 0.1f;
				frameAcum += deltaTime;
				if (frameAcum > frameTime) {
					currFrame++;
					if (currFrame > maxFrame) currFrame = 0;
					frameAcum -= frameTime;
				}
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
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			}
			if (isDucking) {
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
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
			}
			if (isDucking) {
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

		if (isThrowing) {
			if (direction == LEFT)
				texture = RESOURCE_MANAGER.getTexture("SuperMarioThrowingFireball_LEFT_0");
			else
				texture = RESOURCE_MANAGER.getTexture("SuperMarioThrowingFireball_RIGHT_0");
		
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
			if (velocity.x == 0 && !isDucking) {
				if (direction == RIGHT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0");
				else if (direction == LEFT)
					texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
			}
			if (isDucking) {
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
	}
	}

	if (Mario_sprite == STATE_TRANSITIONING_FROM_SMALL_TO_SUPER) {
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
		if (direction == RIGHT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0");
		}
		else if (direction == LEFT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
		}
	} else if (Mario_sprite == STATE_TRANSITIONING_FROM_SUPER_TO_FIREBALL) {
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
		if (direction == RIGHT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SuperMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningFireMario_RIGHT_0");
			}
		}
		else if (direction == LEFT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SuperMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningFireMario_LEFT_0");
			}
		}	
	}
	else if (Mario_sprite == STATE_TRANSITIONING_FROM_FIREBALL_TO_SMALL) {
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
		if (direction == RIGHT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningFireMario_RIGHT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_RIGHT_0");
		}
		else if (direction == LEFT) {
			if (transitionCurrentFrame == 0) {
				texture = RESOURCE_MANAGER.getTexture("SmallMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 1) {
				texture = RESOURCE_MANAGER.getTexture("TransitioningFireMario_LEFT_0");
			}
			else if (transitionCurrentFrame == 2)
				texture = RESOURCE_MANAGER.getTexture("Fire_Mario_LEFT_0");
		}
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
	Mario_sprite = NORMAL;
	maxFrame = 2;
}

void Mario::TransitionMarioState()
{
	RESOURCE_MANAGER.playSound("PLAYER_POWERUP");
	if (Mario_State == STATE_SMALL)
		Mario_sprite = STATE_TRANSITIONING_FROM_SMALL_TO_SUPER;
	else if (Mario_State == STATE_SUPER)
		Mario_sprite = STATE_TRANSITIONING_FROM_SUPER_TO_FIREBALL;
	else if (Mario_State == STATE_FIRE_BALL)
		Mario_sprite = STATE_TRANSITIONING_FROM_FIREBALL_TO_SMALL;
}

void Mario::ThrowingFireBalls()
{
	isThrowing = true;
	RESOURCE_MANAGER.playSound("PLAYER_FIREBALL");
	if (direction == RIGHT) {
		Vector2 velFb = Vector2Add(Vector2{500, -200}, this->velocity);
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, velFb, RIGHT, 2));
	}
	else if (direction == LEFT) {
		Vector2 velFb = Vector2Add(Vector2{ -500, -200}, this->velocity);
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, velFb, LEFT, 2));
	}
}

std::list<FireBall*> *Mario::getFireBalls()
{
	return &fireballs;
}

float Mario::getAccelerationX() const
{
	return accelerationX;
}

void Mario::reset()
{
	setPosition({ 16, 500 });
	setVel({ 0, 0 });
	direction = RIGHT;
	texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
	isThrowing = isDucking = false;
	Mario_State = STATE_SMALL;
	state = FALLING;

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

void Mario::Ducking() {
	this->isDucking = true;
	velocity.y = 0;
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
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	//if (state != ON_GROUND) 
	if (velocity.y > 50) 
		state = FALLING;

	velocity.y += GRAVITY * deltaTime;

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
	updateCollision();
}

void Mario::draw()
{
	UpdateTexture();
	for (auto& fireball : fireballs) {
		fireball->UpdateTexture();
		fireball->draw();
	}

	DrawTexture(texture, position.x, position.y, WHITE);

	// for debug
	CollEast.draw();
	CollSouth.draw();
	CollNorth.draw();
	CollWest.draw();
}
