#include "../include/Character.h"
#include"../include/Item.h"
#include"../include/Enemy.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"
#include "../include/SmokeEffect.h"
#include "../include/GameEngine.h"
#include "../include/Blocks.h"
#include"../include/Mushroom.h"
#include"../include/Flower.h"
#include"../include/Star.h"
#include"../include/Coin.h"
#include "../include/DustEffect.h"
#include "../include/Moon.h"
#include "../include/MovingBlock.h"

Character::Character():
	Character({ 32, 400 }, { 0, 0 })
{
}

Character::Character(Vector2 pos, Vector2 size):
	Character(pos, size, STATE_SMALL)
{
}

Character::Character(Vector2 pos, Vector2 sz, CharacterState characterstate):
	Character(pos, sz, characterstate, MARIO) // default is mario
{
	cout << "Character created" << endl;
}

Character::Character(Vector2 pos, Vector2 sz, CharacterState characterstate, CharacterType characterType):
	Entity(pos, sz, Vector2{ 0, 0 }, RIGHT, FALLING, 0.1f, 1, WHITE),
	isducking(false),
	scores(0),
	coins(0),
	lives(3),
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
	victory(false),
	exitlevel(false),
	countImmortalTime(0.f),
	countThrowTime(0.f),
	invicibleStarTime(0.f),
	sinkingTime(0.f),
	movingBlockStandOn(nullptr),
	specificVelocity({ 0, 0 })
{
	std::cout << "Character created with size: " << size.x << ", " << size.y << std::endl;

	if (characterType == MARIO) {
		texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
		size = { 32, 40 };
	}
	else if (characterType == LUIGI) {
		texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
		size = { 32, 44 };
	}
	else if (characterType == PEACH) {
		texture = RESOURCE_MANAGER.getTexture("SmallPeach_RIGHT_0");
		size = { 26, 46 };
	}
	else if (characterType == MARISA) {
		texture = RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0");
		size = { 37, 54 };
	}
	else if (characterType == TOAD) {
		texture = RESOURCE_MANAGER.getTexture("SmallToad_RIGHT_0");
		size = { 32, 40 };
	}
	else {
		throw std::runtime_error("Unknown character type");
	}
	
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	CollNorth.setColor(RED);
	CollSouth.setColor(GREEN);
	CollWest.setColor(BLUE);
	CollEast.setColor(BLACK);

	

	// set the transitioning
	// for mario
	transitionFrames = {
		{"SmallMario", {32, 40}, STATE_SMALL, 1}, // 0. small
		{"TransitioningMario", {32, 56}, STATE_SUPER, 2}, // 1. pre super
		{"SuperMario", {32, 56}, STATE_SUPER, 2}, // 2. super
		{"TransitioningFireMario", {32, 56}, STATE_FIRE, 2}, // 3. prefire
		{"FireMario", {32, 56}, STATE_FIRE, 2}, // 4. fire
		{"StarSmallMario", {32, 40}, STATE_STAR, 1}, // 5. star
		{"StarTransitioningMario", {32, 56}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"StarSuperMario", {32, 56}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"StarTranisitioningFireMario", {32, 56}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"StarFireMario", {32, 56}, STATE_FIRESTAR, 2} // 9. firestar
	};
	// for luigi
	transitionFramesLuigi = {
		{"SmallLuigi" , {32, 44}, STATE_SMALL, 1}, // 0. small
		{"TransitioningLuigi", {32, 60}, STATE_SUPER, 2}, // 1. pre super
		{"SuperLuigi", {32, 60}, STATE_SUPER, 2}, // 2. super
		{"TransitioningFireLuigi", {32, 60}, STATE_FIRE, 2}, // 3. prefire
		{"FireLuigi", {32, 60}, STATE_FIRE, 2}, // 4. fire
		{"SmallLuigi", {32, 44}, STATE_STAR, 1}, // 5. star
		{"TransitioningLuigi", {32, 60}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"SuperLuigi" , {32, 60}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"TranisitioningFireLuigi", {32, 60}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"FireLuigi", {32, 60}, STATE_FIRESTAR, 2} // 9. firestar
	};
	// for peach
	transitionFramesPeach = {
		{"SmallPeach", {26, 46}, STATE_SMALL, 2}, // 0. small
		{"SmallPeach", {36, 64}, STATE_SUPER, 2}, // 1. pre super
		{"SuperPeach" , {36, 64}, STATE_SUPER, 2}, // 2. super
		{"FirePeach" , {36, 64}, STATE_FIRE, 2}, // 3. prefire
		{"FirePeach", {36, 64}, STATE_FIRE, 2}, // 4. fire
		{"SmallPeach", {26, 46}, STATE_STAR, 2}, // 5. star
		{"SmallPeach", {36, 64}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"SuperPeach", {36, 64}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"FirePeach", {36, 64}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"FirePeach", {36, 64}, STATE_FIRESTAR, 2} // 9. firestar
	};
	// for marisa
	transitionFramesMarisa = {
		{"SmallMarisa", {37, 54}, STATE_SMALL, 2}, // 0. small
		{"SmallMarisa", {51, 61}, STATE_SUPER, 2}, // 1. pre super
		{"SuperMarisa" , {51, 61}, STATE_SUPER, 2}, // 2. super
		{"FireMarisa" , {51, 61}, STATE_FIRE, 2}, // 3. prefire
		{"FireMarisa", {51, 61}, STATE_FIRE, 2}, // 4. fire
		{"SmallMarisa", {37, 54}, STATE_STAR, 2}, // 5. star
		{"SmallMarisa", {51, 61}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"SuperMarisa", {51, 61}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"FireMarisa", {51, 61}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"FireMarisa", {51, 61}, STATE_FIRESTAR, 2} // 9. firestar
	};
	// for Toad
	transitionFramesToad = {
		{"SmallToad", {32, 40}, STATE_SMALL, 1}, // 0. small
		{"TransitioningToad", {32, 56}, STATE_SUPER, 2}, // 1. pre super
		{"SuperToad", {32, 56}, STATE_SUPER, 2}, // 2. super
		{"TransitioningFireToad", {32, 56}, STATE_FIRE, 2}, // 3. prefire
		{"FireToad", {32, 56}, STATE_FIRE, 2}, // 4. fire
		{"SmallToad", {32, 40}, STATE_STAR, 1}, // 5. star
		{"TransitioningToad", {32, 56}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"SuperToad", {32, 56}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"TranisitioningFireToad", {32, 56}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"FireToad", {32, 56}, STATE_FIRESTAR, 2} // 9. firestar
	};
}

Character::~Character()
{
}

EntityType Character::getEntityType() const
{
	return CHARACTER;
}

// reset when die & continue with that level 
void Character::resetInGame(){
	setPosition({ 32, 400 });
	Character_state = STATE_SMALL;
	if (characterType == MARIO) {
		texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
		size = { 32, 40 };
	}
	else if (characterType == LUIGI) {
		texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
		size = { 32, 44 };
	}
	else if (characterType == PEACH) {
		texture = RESOURCE_MANAGER.getTexture("SmallPeach_RIGHT_0");
		size = { 26, 46 };
	}
	else if (characterType == MARISA) {
		texture = RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0");
		size = { 37, 54 };
	}
	else if (characterType == TOAD) {
		texture = RESOURCE_MANAGER.getTexture("SmallToad_RIGHT_0");
		size = { 32, 40 };
	}
	else {
		throw std::runtime_error("Unknown character type");
	}
	//this->size = { (float)texture.width, (float)texture.height };
	setVel({ 0, 0 });
	scores = 0;
	coins = 0;
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
	isThrowing = isducking = false;
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	victory = false;
	exitlevel = false;
	movingBlockStandOn = nullptr; // reset moving block stand on
	specificVelocity = { 0, 0 };
}

// reset when changing map (reset all)
void Character::reset()
{
	Character_state = STATE_SMALL;
	if (characterType == MARIO) {
		texture = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
		size = { 32, 40 };
	}
	else if (characterType == LUIGI) {
		texture = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
		size = { 32, 44 };
	}
	else if (characterType == PEACH) {
		texture = RESOURCE_MANAGER.getTexture("SmallPeach_RIGHT_0");
		size = { 26, 46 };
	}
	else if (characterType == MARISA) {
		texture = RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0");
		size = { 37, 54 };
	}
	else if (characterType == TOAD) {
		texture = RESOURCE_MANAGER.getTexture("SmallToad_RIGHT_0");
		size = { 32, 40 };
	}
	else {
		throw std::runtime_error("Unknown character type");
	}
	setGravityAvailable(true);
	setCollisionAvailable(true);
	setPosition({ 32, 400 });
	setVel({ 0, 0 });
	direction = RIGHT;
	scores = 0;
	coins = 0;
	lives = 3;
	phase = DEFAULT_PHASE;
	isjumping = false;
	holding = false;
	lostLife = false;
	invicibleStarTime = 0.f;
	countThrowTime = 0.f;
	countImmortalTime = 0.f;
	isThrowing = isducking = false;
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	victory = false;
	exitlevel = false;
	movingBlockStandOn = nullptr; // reset moving block stand on
	specificVelocity = { 0, 0 };
}

void Character::setPhase(Phase phase)
{
	if (phase == DEAD_PHASE) {
		setVelX(0.f);
		setVelY(-DEAD_PLAYER_INITIAL_VELOCITY);
		setCollisionAvailable(false);
		setMovingBlockStandOn(nullptr); 
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

const CharacterState& Character::getCharacterState() const
{
	return Character_state;
}

void Character::setMovingBlockStandOn(MovingBlock* block) {
	this->movingBlockStandOn = block;
}

MovingBlock* Character::getMovingBlockStandOn() const {
	return this->movingBlockStandOn;
}

void Character::ResetEnterNewMap()
{
	if (movingBlockStandOn != nullptr) {
		movingBlockStandOn = nullptr; // reset moving block stand on
	}
	isjumping = false;
	isducking = false;
	lostLife = false;
	countThrowTime = 0.f;
	sinkingTime = 0.f;
	takeDamage = true;
	timeNoTakeDamage = 0.f;
	victory = false;
	exitlevel = false;
	transitioningFrameAcum = 0.f;
	state = FALLING;
	position = { 32, 400 };
	velocity = { 0, 0 };
	collisionAvailable = true;
	gravityAvailable = true;
	phase = DEFAULT_PHASE;
	Character_state = STATE_SMALL;
}

bool Character::isInvicible() const
{
	return invicibleStarTime > 0.f;
}

bool Character::isImmortal() const
{
	return countImmortalTime > 0.f;
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

float Character::getSinkingTime() const
{
	return sinkingTime;
}

bool Character::isHolding() const
{
	return holding;
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

void Character::setCharacterState(CharacterState characterState)
{
	this->Character_state = characterState;
}

void Character::setHolding(bool holding)
{
	this->holding = holding;
}

void Character::setSinkingTime(float sinkingTime) {
	this->sinkingTime = sinkingTime;
}

void Character::lostSuit()
{
	if (Character_state == STATE_SMALL) {
		setLostLife(true);
		return;
	}
	countImmortalTime = 15.f * transitioningFrameTime;
	if (IsKeyPressed(KEY_P)) {
		cout << "transitionFrametime: " << transitioningFrameTime << endl;
	}
	//lostSuitTrigger = false;
	if (Character_state == STATE_SUPER) {
		StartTransition({ 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0 }, 15);
	}
	else if (Character_state == STATE_FIRE) {
		StartTransition({ 4, 3, 4, 3, 4, 3, 4, 3, 0, 3, 0, 3, 0, 3, 0 }, 15);
	}
	else if (Character_state == STATE_STAR) {
		StartTransition({ 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 }, 14);
	}
	else if (Character_state == STATE_SUPERSTAR) {
		StartTransition({ 7, 2, 7, 2, 7, 2, 7, 2, 7, 2, 7, 2, 7, 2 }, 14);
	}
	else if (Character_state == STATE_FIRESTAR) {
		StartTransition({ 9, 4, 9, 4, 9, 4, 9, 4, 9, 4, 9, 4, 9, 4 }, 14);
	}
}

void Character::setLostLife(bool lostLife)
{
	this->lostLife = lostLife;
}

void Character::Jumping()
{
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("jump.wav");
	float speedY = MAXSPEED_Y;
	velocity.y = -speedY;
	state = JUMPING;
}

void Character::Standing()
{
	const float deltaTime = GetFrameTime();
	if (velocity.x > 0) {
		velocity.x -= DECEL_X * deltaTime;
	}
	else if (velocity.x < 0) {
		velocity.x += DECEL_X * deltaTime;
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
	const float deltaTime = GetFrameTime();

	if (isInvicible()) {
		invicibleStarTime -= deltaTime;
		if (invicibleStarTime <= 0.f)
			invicibleStarTime = 0.f;
	}
	else {

		if (!lostSuitTrigger && (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR)) {
			lostSuit();
			lostSuitTrigger = true;
		}
	}
	// time for take damage
	timeNoTakeDamage -= GetFrameTime();
	if (timeNoTakeDamage <= 0.f) {
		timeNoTakeDamage = 0.f;
		// character will take damaged when true
		takeDamage = true;
	}
	else {
		takeDamage = false;
	}

	specificVelocity = getVelocity();

	if (movingBlockStandOn != nullptr) {
		setVelX(specificVelocity.x + movingBlockStandOn->getVelocity().x);
		setVelY(specificVelocity.y + movingBlockStandOn->getVelocity().y);
	}

	// physics
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	setVel(specificVelocity);
	
	if (velocity.y > 20 && state != SINKING)
		state = FALLING;
	velocity.y += CHARACTER_GRAVITY * deltaTime + 2;
	if (state == SINKING) { 
		sinkingTime -= deltaTime;
		velocity.y = CHARACTER_GRAVITY / 32;
		if (sinkingTime <= 0.f) {
			state = FALLING;
		}
	}
	// fireball
	for (auto i = fireballs.begin(); i != fireballs.end();) {
		FireBall* fireball = *i;
		if (fireball->ismaxTime()) {
			delete fireball;
			fireball = nullptr;
			i = fireballs.erase(i);
		}
		else {
			fireball->Update();
			++i;
		}
	}
	// lost suit sound
	if (phase == DEFAULT_PHASE) {
		if (countImmortalTime > 0.f) {
			countImmortalTime = max(0.f, countImmortalTime - deltaTime);
			if (SETTING.isSoundEnabled()) 
				RESOURCE_MANAGER.playSound("lost_suit.wav");
		}
	}
	if (characterType == MARIO || characterType == TOAD) {
		size = (Character_state == STATE_SMALL || Character_state == STATE_STAR) ? Vector2{ 32, 40 } : Vector2{ 32, 56 };
	}
	else if (characterType == LUIGI)
		size = (Character_state == STATE_SMALL || Character_state == STATE_STAR) ? Vector2{ 32, 44 } : Vector2{ 32, 60 };
	else if (characterType == PEACH) {
		size = (Character_state == STATE_SMALL || Character_state == STATE_STAR) ? Vector2{ 26, 46 } : Vector2{ 36, 64 };
	}
	else if (characterType == MARISA) {
		size = (Character_state == STATE_SMALL || Character_state == STATE_STAR) ? Vector2{ 37, 54 } : Vector2{ 51, 61 };
	}
	updateCollision();
	UpdateTexture();
}

void Character::draw()
{
	for (auto& fireball : fireballs) {
		fireball->draw();
	}

	if (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR) {
		Color rainbowTint = RESOURCE_MANAGER.getRainbowTint(GetTime());
		DrawTexture(texture, position.x, position.y, rainbowTint);
	}
	else
		DrawTexturePro(texture, { 0, 0, (float)texture.width, (float)texture.height },
			{ position.x, position.y, size.x, size.y }, { 0, 0 }, 0.0f, WHITE);
		//DrawTexture(texture, position.x, position.y, WHITE);
	// for debug
	if (SETTING.getDebugMode()) {
		CollEast.draw();
		CollSouth.draw();
		CollNorth.draw();
		CollWest.draw();
	}
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
	if (state == ON_GROUND || state == SINKING) {
		if (IsKeyPressed(KEY_UP)) {
			Jumping();
		}
		if (IsKeyDown(KEY_DOWN)) {
			Ducking();
		}
		else isducking = false;
	}

	if (state == JUMPING) {
		if (velocity.y < 0) {
			if (IsKeyReleased(KEY_UP))
				this->velocity.y *= 0.5;
		}
	}
	if (IsKeyPressed(KEY_F1))
		eatGreenMushrooms();
	if (IsKeyPressed(KEY_F2))
		eatRedMushrooms();
	if (IsKeyPressed(KEY_F3))
		eatFireFlower();
	if (IsKeyPressed(KEY_F4))
		eatStar();
	if (IsKeyPressed(KEY_L))
		lostSuit();
	if (IsKeyPressed(KEY_LEFT_CONTROL) && (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR) && !isducking) {
		ThrowingFireBalls();
	}
}

void Character::HandleInput(int leftKey, int rightKey, int upKey, int downKey, int fireKey)
{
	if (IsKeyDown(leftKey))
		RunLeft();
	else if (IsKeyDown(rightKey))
		RunRight();
	else Standing();

	if (state == ON_GROUND || state == SINKING) {
		if (IsKeyPressed(upKey)) {
			Jumping();
		}
		if (IsKeyDown(downKey) && characterType != MARISA) {
			Ducking();
		}
		else {
			isducking = false;
		}
	}

	if (state == JUMPING && velocity.y < 0 && IsKeyReleased(upKey)) {
		velocity.y *= 0.5f;
	}

	// Power-up / debug keys could be shared or also player-specific
	if (IsKeyPressed(KEY_F1)) eatGreenMushrooms();
	if (IsKeyPressed(KEY_F2)) eatRedMushrooms();
	if (IsKeyPressed(KEY_F3)) eatFireFlower();
	if (IsKeyPressed(KEY_F4)) eatStar();
	if (IsKeyPressed(KEY_L))  lostSuit();

	if (IsKeyPressed(fireKey) && (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR) && !isducking) {
		ThrowingFireBalls();
	}
	if (IsKeyPressed(KEY_T)) { // for debug
		cout << position.x << " " << position.y << endl;
	}
}

void Character::HandleInput(InputHandler& inputHandler1, InputHandler& inputHandler2)
{
	if (playerId == 0) {
		// Player 1 controls
		inputHandler1.handleInput(*this);
	}
	else if (playerId == 1) {
		// Player 2 controls
		inputHandler2.handleInput(*this);
	}
	// Handle character-specific input
	if (IsKeyPressed(KEY_F1)) eatGreenMushrooms();
	if (IsKeyPressed(KEY_F2)) eatRedMushrooms();
	if (IsKeyPressed(KEY_F3)) eatFireFlower();
	if (IsKeyPressed(KEY_F4)) eatStar();
	if (IsKeyPressed(KEY_L))  lostSuit();
	if (IsKeyPressed(KEY_T)) { // for debug
		cout << position.x << " " << position.y << endl;
	}
}

void Character::updateCollision() // update the hitbox (4 rectangle in 4 side of character)
{
	if (isducking) {
		if (characterType == MARIO || characterType == LUIGI || characterType == TOAD) {
			CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + size.y / 2 - CollNorth.getHeight() });
			CollEast.setSize({ 5, size.y / 2 });
			CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + size.y * 3 / 4 - CollEast.getHeight() / 2 });
			CollWest.setSize({ 5, size.y / 2 });
			CollWest.setPos({ position.x , position.y + size.y * 3 / 4 - CollWest.getHeight() / 2 });
		}
		else if (characterType == PEACH) {
			CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + size.y / 2 - CollNorth.getHeight() - 10.f});
			CollEast.setSize({ 5, size.y / 2 });
			CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + size.y / 2 - CollEast.getHeight() / 2 + 10.f});
			CollWest.setSize({ 5, size.y / 2 });
			CollWest.setPos({ position.x , position.y + size.y / 2 - CollWest.getHeight() / 2 + 10.f});
		}
		else if (characterType == MARISA) {
			if (Character_state == STATE_SMALL || Character_state == STATE_STAR) {
				size = { 55, 41 };
			}
			else {
				size = { 62, 46 };
			}
			CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + 15 - CollNorth.getHeight() });
			CollNorth.setSize({ size.x - 5, CollNorth.getHeight() });

			CollSouth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + 15 + size.y - CollSouth.getHeight()});
			CollSouth.setSize({ size.x - 5, CollSouth.getHeight() });

			CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + 30 - CollEast.getHeight() / 2 });
			CollEast.setSize({ 5, size.y / 2 });

			CollWest.setPos({ position.x, position.y + 30 - CollWest.getHeight() / 2});
			CollWest.setSize({ 5, size.y / 2 });
		}
	}
	else {
		CollWest.setSize({ 5, size.y - 5 });
		CollEast.setSize({ 5, size.y - 5 });
		
		Entity::updateCollision();
	}
	//cout << size.x << " " << size.y << endl;
}

void Character::UpdateTexture()
{
	std::string charactertype;
	if (characterType == MARIO)
		charactertype = "Mario";
	else if (characterType == LUIGI)
		charactertype = "Luigi";
	else if (characterType == PEACH)
		charactertype = "Peach";
	else if (characterType == MARISA)
		charactertype = "Marisa";
	else if (characterType == TOAD)
		charactertype = "Toad";

	std::string characterDir = getDir() == RIGHT ? "_RIGHT_" : "_LEFT_";
	std::string characterState;

	if (characterType == PEACH) {
		if (Character_state == STATE_SMALL || Character_state == STATE_STAR)
			characterState = "Small";
		else if (Character_state == STATE_SUPER || Character_state == STATE_SUPERSTAR)
			characterState = "Super";
		else if (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR)
			characterState = "Fire";
		maxFrame = 2;
	}
	else if (characterType == TOAD || characterType == LUIGI) {
		if (Character_state == STATE_SMALL || Character_state == STATE_STAR){
			characterState = "Small";
			maxFrame = 1;
		}
		else if (Character_state == STATE_SUPER || Character_state == STATE_SUPERSTAR) {
			characterState = "Super";
			maxFrame = 2;
		}
		else if (Character_state == STATE_FIRE || Character_state == STATE_FIRESTAR) {
			characterState = "Fire";
			maxFrame = 2;
		}
	}
	else {
		// for mario
		if (Character_state == STATE_SMALL) {
			characterState = "Small";
			maxFrame = 1;
		}
		else if (Character_state == STATE_SUPER) {
			characterState = "Super";
			maxFrame = 2;
		}
		else if (Character_state == STATE_FIRE) {
			characterState = "Fire";
			maxFrame = 2;
		}
		else if (Character_state == STATE_STAR) {
			characterState = "StarSmall";
			maxFrame = 1;
		}
		else if (Character_state == STATE_SUPERSTAR) {
			characterState = "StarSuper";
			maxFrame = 2;
		}
		else if (Character_state == STATE_FIRESTAR) {
			characterState = "StarFire";
			maxFrame = 2;
		}
	}


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
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + characterDir + std::to_string(currFrame));
		if (velocity.x == 0 && !isducking)
			// idling
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + characterDir + "0");
		if (isducking) {
			setVelX(0.f);
			texture = RESOURCE_MANAGER.getTexture(characterState + charactertype + "Ducking" + characterDir + "0");
		}
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

	UpdateTransitioningTexture();
}

// 0. small
// 1. presuper
// 2. super
// 3. prefire
// 4. fire
// 5. star
// 6. pre superstar
// 7. superstar
// 8. pre firestar
// 9. firestar

void Character::StartTransition(const std::vector<int>& frameOrder, int steps) {
	this->transitionFrameOrder = frameOrder;
	transitionCurrentFrame = 0;
	transitionSteps = steps;
	transitionCurrentFrame = frameOrder[0];
	transitioningFrameAcum = 0;
	transitionCurrentFramePos = 0;
}

void Character::ReleaseRunFast()
{
	if (state == ON_GROUND || state == SINKING) {
		float dt = GetFrameTime();
		float targetSpeed = MAX_WALK_SPEED_X; // mục tiêu khi thả shift
		float decelAmount = DECEL_X * dt;     // giảm tốc mỗi frame

		if (direction == RIGHT && velocity.x > targetSpeed) {
			velocity.x -= decelAmount;
			if (velocity.x < targetSpeed) {
				velocity.x = targetSpeed; // chặn không giảm quá
			}
		}
		else if (direction == LEFT && velocity.x < -targetSpeed) {
			velocity.x += decelAmount;
			if (velocity.x > -targetSpeed) {
				velocity.x = -targetSpeed; // chặn không giảm quá
			}
		}
	}
}


void Character::RunFast()
{
	float deltaTime = GetFrameTime();
	if (state == ON_GROUND || state == SINKING) {
		if (direction == RIGHT) {
			if (velocity.x < 0) 
				velocity.x = 0;
			velocity.x += ACCEL_X * deltaTime * 1.5;
			if (velocity.x >= MAX_RUN_SPEED_X) {
				velocity.x = MAX_RUN_SPEED_X;
			}
		}
		else if (direction == LEFT) {
			if (velocity.x > 0) 
				velocity.x = 0;
			velocity.x -= ACCEL_X * deltaTime * 1.5;
			if (velocity.x <= -MAX_RUN_SPEED_X) {
				velocity.x = -MAX_RUN_SPEED_X;
			}
		}
	}
}

void Character::RunLeft()
{
	float deltaTime = GetFrameTime();
	if (direction == RIGHT) {
		if (velocity.x > 70 && state == ON_GROUND) {
			if (SETTING.isSoundEnabled()) {
				RESOURCE_MANAGER.stopSound("skid.wav");
				RESOURCE_MANAGER.playSound("skid.wav");
			}
			SmokeEffect* smoke = new SmokeEffect(Vector2{ position.x + size.x / 2, position.y + size.y / 2 }, { 50, -50 });
			globalGameEngine->addEffect(smoke);
		}
		direction = LEFT;
		velocity.x = 0;
	}

	float speed = MAX_WALK_SPEED_X;
	if (abs(velocity.x) + ACCEL_X * deltaTime >= speed) {
		velocity.x = -speed;
	}
	else {
		velocity.x -= ACCEL_X * deltaTime;
	}
}

void Character::RunRight()
{
	float deltaTime = GetFrameTime();
	if (direction == LEFT) {
		if (velocity.x < -70 && state == ON_GROUND) {
			if (SETTING.isSoundEnabled()) {
				RESOURCE_MANAGER.stopSound("skid.wav");
				RESOURCE_MANAGER.playSound("skid.wav");
			}
			SmokeEffect* smoke = new SmokeEffect(Vector2{ position.x + size.x / 2, position.y + size.y / 2}, { -50, -50 });
			globalGameEngine->addEffect(smoke);
		}
		direction = RIGHT;
		velocity.x = 0;
	}
	float speed = MAX_WALK_SPEED_X;
	if (velocity.x + ACCEL_X * deltaTime >= speed) {
		velocity.x = speed;
	}
	else {
		velocity.x += ACCEL_X * deltaTime;
	}
}

void Character::UpdateTransitioningTexture()
{
	if (transitionFrameOrder.empty()) return;

	const float deltaTime = GetFrameTime();
	transitioningFrameAcum += deltaTime;
	if (transitioningFrameAcum >= transitioningFrameTime) {
		transitioningFrameAcum = 0;
		transitionCurrentFramePos++;
		if (transitionCurrentFramePos < transitionFrameOrder.size()) {
			transitionCurrentFrame = transitionFrameOrder[transitionCurrentFramePos];
		}
		else {
			transitionCurrentFramePos = 0;
			TransitionFrame& lastframe = transitionFrames[transitionFrameOrder.back()];
			Character_state = lastframe.FinalState;
			this->size = lastframe.size;
			this->maxFrame = lastframe.Max_frame;
			updateCollision();
			transitionFrameOrder.clear();
			return;
		}
	}

	TransitionFrame frame;
	if (characterType == MARIO)
		frame = transitionFrames[transitionCurrentFrame];
	else if (characterType == LUIGI)
		frame = transitionFramesLuigi[transitionCurrentFrame];
	else if (characterType == TOAD)
		frame = transitionFramesToad[transitionCurrentFrame];
	else if (characterType == PEACH)
		frame = transitionFramesPeach[transitionCurrentFrame];
	else if (characterType == MARISA)
		frame = transitionFramesMarisa[transitionCurrentFrame];

	std::string dir = this->direction == RIGHT ? "_RIGHT_" : "_LEFT_";
	texture = RESOURCE_MANAGER.getTexture(frame.textureKey + dir + "0");
	this->size = frame.size;
	this->maxFrame = frame.Max_frame;
	updateCollision();
}

float Character::getAcclerationX() const
{
	return ACCEL_X;
}
void Character::ThrowingFireBalls()
{
	isThrowing = true;
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("fireball.wav");
	if (direction == RIGHT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2 - 5, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{250, -250}, RIGHT, 2));
	else if (direction == LEFT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2 - 5, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{-250, -250}, LEFT, 2));
}
void Character::collisionWithItem(const Item* item)
{
	Effect* score = nullptr;
	DustEffect* dust = nullptr;
	if (item->getItemType() == MUSHROOM) {
		const Mushroom* mushroom = dynamic_cast<const Mushroom*>(item);
		if (mushroom->getMushroomType() == REDMUSHROOM) {
			scores += mushroom->getPoint();
			eatRedMushrooms();
			score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string((int)mushroom->getPoint()).c_str()), Vector2{ mushroom->getX(), mushroom->getTop() });
		}
		else if (mushroom->getMushroomType() == GREENMUSHROOM) {
			eatGreenMushrooms();
			score = new ScoreEffect(RESOURCE_MANAGER.getTexture("gui1Up"), Vector2{ mushroom->getX(), mushroom->getTop() });
		}	
		dust = new DustEffect(Vector2{ mushroom->getX(), mushroom->getY() });
	}
	else if (item->getItemType() == MOON) {
		const Moon* moon = dynamic_cast<const Moon*>(item);
		lives += 3;
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("1-up.wav");
		score = new ScoreEffect(RESOURCE_MANAGER.getTexture("gui3Up"), Vector2{ moon->getX(), moon->getTop() });
		dust = new DustEffect(Vector2{ moon->getX(), moon->getY() });
	}
	else if (item->getItemType() == STAR) {
		const Star* star = dynamic_cast<const Star*>(item);
		eatStar();
		if (star->getStarType() == YELLOW_STAR) 
			invicibleStarTime = 12.f;
		else if (star->getStarType() == BLUE_STAR)
			invicibleStarTime = 18.f;
		scores += star->getPoint();
		score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string((int)star->getPoint()).c_str()), Vector2{ star->getX(), star->getTop() });
		dust = new DustEffect(Vector2{ star->getX(), star->getY() });
	}
	else if (item->getItemType() == FLOWER) {
		const Flower* flower = dynamic_cast<const Flower*>(item);
		if (flower->getFlowerType() == FIRE_FLOWER) {
			scores += flower->getPoint();
			eatFireFlower();
			score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string((int)flower->getPoint()).c_str()), Vector2{ flower->getX(), flower->getTop() });
		}
		dust = new DustEffect(Vector2{ flower->getX(), flower->getY() });

	}
	else if (item->getItemType() == COIN) {
		const Coin* coin = dynamic_cast<const Coin*>(item);
		if (coin->getCoinType() == STATIC_COIN) {
			coins++;
			scores += coin->getPoint();
			score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string((int)coin->getPoint()).c_str()), Vector2{ coin->getX(), coin->getTop() });
			if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("coin.wav");
		}
		dust = new DustEffect(Vector2{ coin->getX(), coin->getY() });

	}
	if (score != nullptr) {
		globalGameEngine->addEffect(score);
	}
	if (dust != nullptr)
		globalGameEngine->addEffect(dust);
}

void Character::collisionWithEnemy(Enemy* enemy, CollisionType CollType)
{
	if (!enemy) return;
	if (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR) {
		// attacked
		scores += enemy->getScores();
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
		enemy->stomped();
		
	}
	else if (enemy->getEnemyType() != SHELL) {
		if (countImmortalTime > 0.f)
			return;
		else if (CollType != COLLISION_TYPE_SOUTH || enemy->getEnemyType() == PIRANHA || enemy->getEnemyType() == MUNCHER || enemy->getEnemyType() == SPINY) {
			lostSuit();
		}
		else  {
			// stomped
			scores += enemy->getScores();
			setVelY(jet_stomp_velocity);
			setJumping(true);
			if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
			enemy->stomped();
			SmokeEffect* smokeright = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{60, -120});
			globalGameEngine->addEffect(smokeright);
			SmokeEffect* smokeleft = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{ -60, -120 });
			globalGameEngine->addEffect(smokeleft);
		}
	}
	else if (enemy->getEnemyType() == SHELL) {
		if (CollType == COLLISION_TYPE_SOUTH || CollType == COLLISION_TYPE_NORTH) {
			if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
			enemy->stomped();
			setVelY(jet_stomp_velocity);
			setJumping(true);
			SmokeEffect* smokeright = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{ 60, -120 });
			globalGameEngine->addEffect(smokeright);
			SmokeEffect* smokeleft = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{ -60, -120 });
			globalGameEngine->addEffect(smokeleft);
		}
		else {
			if (!enemy->getIsKicked()) {
				Direction dir = CollType == COLLISION_TYPE_EAST ? LEFT : RIGHT;
				enemy->kicked(dir);
				timeNoTakeDamage = 0.3f;
				if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("kick.wav");
			}
			else if (countImmortalTime > 0.f)
				return;
			else if (takeDamage) {
				lostSuit();
				timeNoTakeDamage = 0.f;
			}
		}
	}
}

void Character::CollisionWithFireball(EnemyFireBall* fireball)
{
	if (countImmortalTime > 0.f) return;
	if (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR) {
		return;
	}
	lostSuit();
	fireball->setEntityDead();
}

std::list<FireBall*>* Character::getFireBalls()
{
	return &fireballs;
}

void Character::loadEntity(const json& j)
{
	Entity::loadEntity(j); // Load base class data

	phase = static_cast<Phase>(j["phase"].get<int>());
	characterType = static_cast<CharacterType>(j["characterType"].get<int>());
	Character_state = static_cast<CharacterState>(j["characterState"].get<int>());
	lostLife = j["lostLife"];
	isducking = j["isducking"];
	scores = j["scores"];
	coins = j["coins"];
	lives = j["lives"];
	invicibleStarTime = j["invicibleStarTime"];
	sinkingTime = j["sinkingTime"];
	// for safe
	frameTime = 0.f;
	frameAcum = 0.f;
	velocity = { 0, 0 };
	//
	holding = j["holding"];
	isThrowing = j["isThrowing"];
	playerId = j["playerId"];
	countThrowTime = j["countThrowTime"];
	countImmortalTime = j["countImmortalTime"];
	standingUp = j["standingUp"];

	transitioningFrameTime = 0.06f;
	transitioningFrameAcum = 0.f;
	transitionSteps = j["transitionSteps"];
	transitionCurrentFrame = j["transitionCurrentFrame"];
	transitionCurrentFramePos = j["transitionCurrentFramePos"];
	throwFrameCounter = j["throwFrameCounter"];
	victoryFrameCounter = j["victoryFrameCounter"];
	victory = j["victory"];
	exitlevel = j["exitlevel"];
	lostSuitTrigger = j["lostSuitTrigger"];
}


void Character::saveEntity(json& j) const
{
	Entity::saveEntity(j); // Save base class data

	j["phase"] = static_cast<int>(phase);
	j["characterType"] = static_cast<int>(characterType);
	j["characterState"] = static_cast<int>(Character_state);
	j["lostLife"] = lostLife;
	j["isducking"] = isducking;
	j["scores"] = scores;
	j["coins"] = coins;
	j["lives"] = lives;
	j["invicibleStarTime"] = invicibleStarTime;
	j["sinkingTime"] = sinkingTime;
	j["playerId"] = playerId;
	j["holding"] = holding;
	j["isThrowing"] = isThrowing;
	j["countThrowTime"] = countThrowTime;
	j["countImmortalTime"] = countImmortalTime;
	j["standingUp"] = standingUp;

	j["transitioningFrameTime"] = transitioningFrameTime;
	j["transitioningFrameAcum"] = 0;
	j["transitionSteps"] = transitionSteps;
	j["transitionCurrentFrame"] = 0;
	j["transitionCurrentFramePos"] = 0;
	j["throwFrameCounter"] = throwFrameCounter;
	j["victoryFrameCounter"] = victoryFrameCounter;
	j["victory"] = victory;
	j["exitlevel"] = exitlevel;
	j["lostSuitTrigger"] = lostSuitTrigger;
}


void Character::setVictory(bool victory)
{
	this->victory = victory;
}

void Character::eatGreenMushrooms() // +1 health
{
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("1-up.wav");
	this->lives++;
}

void Character::eatRedMushrooms() // transform to super
{
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("power_up.wav");
	if (Character_state == STATE_SMALL) {
		StartTransition({ 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 }, 11);
	}
	else if (Character_state == STATE_STAR) {
		StartTransition({ 5, 6, 5, 6, 5, 6, 7, 6, 7, 6, 7 }, 11);
	}
}

void Character::eatStar() // transform to star
{
	lostSuitTrigger = false;
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("power_up.wav");
	if (Character_state == STATE_SMALL) {
		StartTransition({ 0, 5, 0, 5, 0, 5, 0, 5 }, 8);
	}
	else if (Character_state == STATE_SUPER) {
		StartTransition({ 2, 7, 2, 7, 2, 7, 2, 7 }, 8);
	}
	else if (Character_state == STATE_FIRE) {
		StartTransition({ 4, 9, 4, 9, 4, 9, 4, 9 }, 8);
	}
	invicibleStarTime = 12.f;
}

void Character::eatFireFlower() // transform to fire
{
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("power_up.wav");
	if (Character_state == STATE_SMALL) {
		StartTransition({0, 3, 0, 3, 0, 3, 4, 3, 4, 3, 4}, 11);
	}
	else if (Character_state == STATE_SUPER) {
		StartTransition({2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 4}, 11);
	}
	else if (Character_state == STATE_STAR) {
		StartTransition({ 5, 8, 5, 8, 5, 8, 9, 8, 9, 8, 9 }, 11);
	}
}

bool Character::getVictory() const
{
	return victory;
}

bool Character::getExitLevel() const
{
	return exitlevel;
}


