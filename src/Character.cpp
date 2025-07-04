#include "../include/Character.h"

Character::Character():
	Character({32, 400}, {32, 40})
{
}

Character::Character(Vector2 pos, Vector2 size):
	Character(pos, size, STATE_SMALL)
{
}

Character::Character(Vector2 pos, Vector2 sz, CharacterState characterstate):
	Character(pos, sz, characterstate, MARIO) // default is mario
{
	
}

Character::Character(Vector2 pos, Vector2 sz, CharacterState characterstate, CharacterType characterType):
	Entity(pos, { 32, 40 }, Vector2{ 0, 0 }, RIGHT, FALLING, 0.1f, 1, WHITE),
	isducking(false),
	scores(0),
	coins(0),
	lives(5),
	holding(false),
	isThrowing(false),
	standingUp(false),
	lostLife(false),
	phase(DEFAULT_PHASE),
	transitioningFrameTime(0.06),
	transitioningFrameAcum(0),
	transitionSteps(11),
	transitionCurrentFrame(0),
	transitionCurrentFramePos(0),
	Character_state(characterstate),
	characterType(characterType),
	Character_sprite_State(NORMAL),
	victory(false),
	exitlevel(false)
{
	if (characterstate == STATE_SMALL)
		this->size = { 32, 40 };
	else this->size = { 32, 56 };
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	CollNorth.setColor(RED);
	CollSouth.setColor(GREEN);
	CollWest.setColor(BLUE);
	CollEast.setColor(BLACK);
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("luigi_idle_right_0");
}

Character::~Character()
{
}

EntityType Character::getEntityType() const
{
	return CHARACTER;
}

// reset when die & continue with that level 
void Character::resetInGame()
{
	setPosition({ 32, 400 });
	if (Character_state == STATE_SMALL)
		this->size = { 32, 40 };
	else this->size = { 32, 56 };
	setVel({ 0, 0 });
	direction = RIGHT;
	phase = DEFAULT_PHASE;
	collisionAvailable = true;
	gravityAvailable = true;
	isjumping = false;
	holding = false;
	lostLife = false;
	invicibleStarTime = 0.f;
	countThrowTime = 0.f;
	countImmortalTime = 0.f;
	specificVelocity = { 0, 0 };
	isThrowing = isducking = false;
	Character_state = STATE_SMALL;
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("luigi_idle_right_0");
	victory = false;
	exitlevel = false;
}

// reset when changing map (reset all)
void Character::reset()
{
	if (Character_state == STATE_SMALL)
		this->size = { 32, 40 };
	else this->size = { 32, 56 };
	setPosition({ 32, 400 });
	setVel({ 0, 0 });
	direction = RIGHT;
	scores = 0;
	coins = 0;
	lives = 5;
	phase = DEFAULT_PHASE;
	isjumping = false;
	holding = false;
	lostLife = false;
	invicibleStarTime = 0.f;
	countThrowTime = 0.f;
	countImmortalTime = 0.f;
	specificVelocity = { 0, 0 };
	isThrowing = isducking = false;
	Character_state = STATE_SMALL;
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("luigi_idle_right_0");
	victory = false;
	exitlevel = false;
}

void Character::setPhase(Phase phase)
{
	if (phase == DEAD_PHASE) {
		setVelX(0.f);
		setVelY(-DEAD_PLAYER_INITIAL_VELOCITY);
		setCollisionAvailable(false);
		setHolding(false);
		lives--;
	}
	else if (phase == CLEARLEVEL_PHASE) {
		setVelY(0.f);
		setVelX(Max_walk_velocity);
	}
	this->phase = phase;
}

const Phase& Character::getPhase() const
{
	return phase;
}

CharacterState& Character::getCharacterState() 
{
	return Character_state;
}

bool Character::isInvicible() const
{
	return invicibleStarTime > 0.f;
}

bool Character::isDucking() const
{
	return isducking;
}

bool Character::isLostLife() const
{
	return lostLife;
}

bool Character::isIdle() const
{
	return (velocity.x == 0 && velocity.y == 0 && !isDucking() && !isjumping);
}

bool Character::isStandingUp() const
{
	return standingUp;

}

bool Character::isJumping() const
{
	return isjumping;
}

int Character::getLives() const
{
	return lives;
}

int Character::getCoins() const
{
	return coins;
}

int Character::getScores() const
{
	return scores;
}

bool Character::isHolding() const
{
	return holding;
}

void Character::transform(CharacterState newState)
{
}

void Character::setLives(int lives)
{
	this->lives = lives;
}

void Character::setCoins(int coins)
{
	this->coins = coins;
}

void Character::setScores(int scores)
{
	this->scores = scores;
}

void Character::setDucking(bool ducking)
{
	this->isducking = ducking;
}

void Character::setHolding(bool holding)
{
	this->holding = holding;
}

void Character::lostSuit()
{
}

void Character::TransitionToSuper()
{
	this->size = { 32, 56 };
	Character_sprite_State = NORMAL;
	Character_state = STATE_SUPER;
	maxFrame = 2;
}

void Character::TransitionToSmall()
{
	this->size = { 32, 40 };
	Character_sprite_State = NORMAL;
	Character_state = STATE_SMALL;
	maxFrame = 1;
}

void Character::TransitionToFire()
{
	this->size = { 32, 56 };
	Character_sprite_State = NORMAL;
	Character_state = STATE_FIRE_BALL;
	maxFrame = 2;
}

void Character::TransitionState()
{
	RESOURCE_MANAGER.playSound("PLAYER_POWERUP");
	if (Character_state == STATE_SMALL)
		Character_sprite_State = STATE_TRANSITIONING_FROM_SMALL_TO_SUPER;
	else if (Character_state == STATE_SUPER)
		Character_sprite_State = STATE_TRANSITIONING_FROM_SUPER_TO_FIREBALL;
	else if (Character_state == STATE_FIRE_BALL)
		Character_sprite_State = STATE_TRANSITIONING_FROM_FIREBALL_TO_SMALL;
}

void Character::HandleTileCollision(const Tile tile, CollisionType CollType)
{
	if (CollType == COLLISION_TYPE_NONE)
		return;
	switch (CollType) {
	case COLLISION_TYPE_EAST:
		setPosition({ tile.getX() - size.x, position.y });
		velocity.x = 0;
		break;
	case COLLISION_TYPE_NORTH:
		setPosition({ position.x, tile.getY() + tile.getHeight() });
		velocity.y = 0;
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		setPosition({ position.x, tile.getY() - size.y });
		velocity.y = 0;
		state = ON_GROUND;
		break;
	case COLLISION_TYPE_WEST:
		setPosition({ tile.getX() + tile.getWidth(), position.y });
		velocity.x = 0;
		break;
	default:
		break;
	}
}

void Character::setLostLife(bool lostLife)
{
	this->lostLife = lostLife;
}

void Character::Jumping()
{
}

void Character::Standing()
{
	const float deltaTime = GetFrameTime();
	if (velocity.x > 0) {
		velocity.x -= accelerationX * deltaTime;
	}
	else if (velocity.x < 0) {
		velocity.x += accelerationX * deltaTime;
	}
	if (abs(velocity.x) < 20) velocity.x = 0;
}

void Character::Ducking()
{
	this->isducking = true;
	velocity.y = 0;
}

void Character::Update()
{
	HandleInput();
	const float deltaTime = GetFrameTime();
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (velocity.y > 50)
		state = FALLING;
	
	velocity.y += GRAVITY * deltaTime + 2;

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
	UpdateTexture();
}

void Character::draw()
{
	for (auto& fireball : fireballs) {
		fireball->draw();
	}

	if (characterType == MARIO)
		DrawTexture(texture, position.x, position.y, WHITE);
	else {
		Texture2D src = this->texture;
		if (src.id == RESOURCE_MANAGER.getTexture("luigi_jump_right_0").id || src.id == RESOURCE_MANAGER.getTexture("luigi_jump_left_0").id)
			DrawTextureEx(src, { position.x, position.y }, 0.f, 2.65f, WHITE);
		else if (src.id == RESOURCE_MANAGER.getTexture("superluigi_sit_right_0").id ||
			src.id == RESOURCE_MANAGER.getTexture("superluigi_sit_left_0").id ||
			src.id == RESOURCE_MANAGER.getTexture("fireluigi_sit_right_0").id ||
			src.id == RESOURCE_MANAGER.getTexture("fireluigi_sit_left_0").id) 
		{
			DrawTexturePro(src, { 0, 0, (float)src.width, (float)src.height }, { position.x, position.y + size.y / 2, size.x, size.y / 2 }, { 0, 0 }, 0.f, WHITE);
		}
		else DrawTexturePro(src, { 0, 0, (float)src.width, (float)src.height }, { position.x, position.y, size.x, size.y }, { 0, 0 }, 0.f, WHITE);
		//Texture2D jump = RESOURCE_MANAGER.getTexture("luigi_jump_right_0");
		//DrawTexturePro(jump, { 0, 0, (float)jump.width, (float)jump.height }, { position.x + 50, position.y, size.x, size.y }, { 0, 0 }, 0.f, WHITE);
		
	}
	
	// for debug
	/*CollEast.draw();
	CollSouth.draw();
	CollNorth.draw();
	CollWest.draw();*/
}

void Character::HandleInput()
{
	if (IsKeyPressed(KEY_A))
		setLostLife(true);
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
		if (IsKeyDown(KEY_DOWN) && !(characterType == LUIGI && Character_state == STATE_SMALL)) {
			Ducking();
		}
		else isducking = false;
	}
	if (IsKeyPressed(KEY_SPACE)) {
		TransitionState();
	}
	if (IsKeyPressed(KEY_Z) && Character_state != STATE_FIRE_BALL)
		TransitionToFire();
	if (IsKeyPressed(KEY_LEFT_CONTROL) && Character_state == STATE_FIRE_BALL && !isducking) {
		ThrowingFireBalls();
	}
}

void Character::updateCollision()
{
	if (isducking) {
		CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + size.y / 2 - CollNorth.getHeight() });
		CollEast.setSize({ 5, size.y / 2 });
		CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + size.y * 3 / 4 - CollEast.getHeight() / 2 });
		CollWest.setSize({ 5, size.y / 2 });
		CollWest.setPos({ position.x , position.y + size.y * 3 / 4 - CollWest.getHeight() / 2 });
	}
	else {
		CollWest.setSize({ 5, size.y - 5 });
		CollEast.setSize({ 5, size.y - 5 });
		Entity::updateCollision();
	}
}

void Character::UpdateTexture()
{
	
}

float Character::getAcclerationX() const
{
	return accelerationX;
}
void Character::ThrowingFireBalls()
{
	isThrowing = true;
	RESOURCE_MANAGER.playSound("PLAYER_FIREBALL");
	if (direction == RIGHT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{400, -300}, RIGHT, 2));
	else if (direction == LEFT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{-400, -300}, LEFT, 2));
}

std::list<FireBall*>* Character::getFireBalls()
{
	return &fireballs;
}

void Character::setVictory(bool victory)
{
	this->victory = victory;
}

bool Character::getVictory() const
{
	return victory;
}

bool Character::getExitLevel() const
{
	return exitlevel;
}


