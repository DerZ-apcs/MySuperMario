#include "../include/Character.h"
#include"../include/Item.h"
#include"../include/Enemy.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"
#include "../include/GameEngine.h"
#include "../include/Blocks.h"
#include"../include/Mushroom.h"
#include"../include/Flower.h"
#include"../include/Star.h"
#include"../include/Coin.h"

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
	PrevCharacter_state(characterstate),
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
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");

	// set the transitioning
	std::string type = characterType == MARIO ? "Mario" : "Luigi";
	transitionFrames = {
		{"Small" + type, {32, 40}, STATE_SMALL, 1}, // 0. small
		{"Transitioning" + type, {32, 56}, STATE_SUPER, 2}, // 1. pre super
		{"Super" + type, {32, 56}, STATE_SUPER, 2}, // 2. super
		{"TransitioningFire" + type, {32, 56}, STATE_FIRE, 2}, // 3. prefire
		{"Fire" + type, {32, 56}, STATE_FIRE, 2}, // 4. fire
		{"StarSmall" + type, {32, 40}, STATE_STAR, 1}, // 5. star
		{"StarTransitioning" + type, {32, 56}, STATE_SUPERSTAR, 2}, // 6. pre super star
		{"StarSuper" + type, {32, 56}, STATE_SUPERSTAR, 2}, // 7. superstar
		{"StarTranisitioningFire" + type, {32, 56}, STATE_FIRESTAR, 2}, // 8. pre firestar
		{"StarFire" + type, {32, 56}, STATE_FIRESTAR, 2} // 9. firestar
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
void Character::resetInGame()
{
	setPosition({ 32, 400 });
	Character_state = STATE_SMALL;
	this->size = { 32, 40 };
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
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
	victory = false;
	exitlevel = false;
}

// reset when changing map (reset all)
void Character::reset()
{
	Character_state = STATE_SMALL;
	this->size = { 32, 40 };
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
	state = FALLING;
	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });
	updateCollision();
	texture = characterType == MARIO ? RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0") : RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
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

CharacterState& Character::getPrevCharacterState()
{
	return PrevCharacter_state;
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
	if (Character_state == STATE_SMALL) {
		setLostLife(true);
		return;
	}

	countImmortalTime = 15.f * transitioningFrameTime;
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
	RESOURCE_MANAGER.playSound("jump.wav");
	velocity.y = Character_state == MARIO ? -MARIO_MAXSPEEDY : -LUIGI_MAXSPEEDY;
	state = JUMPING;
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

	// physics
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	if (velocity.y > 50)
		state = FALLING;
	velocity.y += GRAVITY * deltaTime + 2;
	// fireball
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
	if (phase == DEFAULT_PHASE) {
		if (countImmortalTime > 0.f) {
			countImmortalTime = max(0.f, countImmortalTime - deltaTime);
			RESOURCE_MANAGER.playSound("lost_suit.wav");
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

	if (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR) {
		Color rainbowTint = RESOURCE_MANAGER.getRainbowTint(GetTime());
		DrawTexture(texture, position.x, position.y, rainbowTint);
	}
	else DrawTexture(texture, position.x, position.y, WHITE);
	//// for debug
	//CollEast.draw();
	//CollSouth.draw();
	//CollNorth.draw();
	//CollWest.draw();
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
	/*if (IsKeyPressed(KEY_SPACE)) {
		TransitionState();
	}*/
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

void Character::updateCollision() // update the hitbox (4 rectangle in 4 side of character)
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
	std::string charactertype = getCharacterType() == MARIO ? "Mario" : "Luigi";
	std::string characterDir = getDir() == RIGHT ? "_RIGHT_" : "_LEFT_";
	std::string characterState;
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

	const float deltaTime = GetFrameTime();
	frameTime = 0.1f;
	frameAcum += deltaTime;
	if (frameAcum > frameTime) {
		currFrame++;
		if (currFrame > maxFrame) currFrame = 0;
		frameAcum -= frameTime;
	}
	if (state == ON_GROUND) {
		if (velocity.x != 0 && !isducking)
			// moving
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

void Character::RunLeft()
{
	float deltaTime = GetFrameTime();
	if (direction == RIGHT) {
		if (velocity.x > 70 && state == ON_GROUND)
			RESOURCE_MANAGER.playSound("skid.wav");
		direction = LEFT;
		velocity.x = 0;
	}

	float speed = Character_state == MARIO ? MARIO_MAXSPEEDX : LUIGI_MAXSPEEDX;
	if (abs(velocity.x) + accelerationX * deltaTime >= speed) {
		velocity.x = -speed;
	}
	else {
		velocity.x -= accelerationX * deltaTime;
	}
}

void Character::RunRight()
{
	float deltaTime = GetFrameTime();
	if (direction == LEFT) {
		if (velocity.x < -70 && state == ON_GROUND)
			RESOURCE_MANAGER.playSound("skid.wav");
		direction = RIGHT;
		velocity.x = 0;
	}
	float speed = Character_state == MARIO ? MARIO_MAXSPEEDX : LUIGI_MAXSPEEDX;
	if (velocity.x + accelerationX * deltaTime >= speed) {
		velocity.x = speed;
	}
	else {
		velocity.x += accelerationX * deltaTime;
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
	const TransitionFrame& frame = transitionFrames[transitionCurrentFrame];
	std::string dir = this->direction == RIGHT ? "_RIGHT_" : "_LEFT_";
	texture = RESOURCE_MANAGER.getTexture(frame.textureKey + dir + "0");
	this->size = frame.size;
	this->maxFrame = frame.Max_frame;
	updateCollision();
}

float Character::getAcclerationX() const
{
	return accelerationX;
}
void Character::ThrowingFireBalls()
{
	isThrowing = true;
	RESOURCE_MANAGER.playSound("fireball.wav");
	if (direction == RIGHT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{400, -300}, RIGHT, 2));
	else if (direction == LEFT) 
		fireballs.push_back(new FireBall(Vector2{ position.x + size.x / 2, position.y + size.y / 2 - 5 }, Vector2{ 16, 16 }, Vector2{-400, -300}, LEFT, 2));
}

void Character::collisionWithItem(const Item* item)
{
	TextEffect* text = nullptr;
	if (item->getItemType() == MUSHROOM) {
		const Mushroom* mushroom = dynamic_cast<const Mushroom*>(item);
		if (mushroom->getMushroomType() == REDMUSHROOM) {
			scores += mushroom->getPoint();
			eatRedMushrooms();
			text = new TextEffect(to_string(mushroom->getPoint()).c_str(), Vector2{ getCenterX(), getTop() });
			text->setTextColor(WHITE);
			text->setOutlineColor(BLACK);
		}
		else if (mushroom->getMushroomType() == GREENMUSHROOM) {
			eatGreenMushrooms();
			text = new TextEffect("1 UP", Vector2{ getCenterX(), getTop() });
			text->setTextColor(WHITE);
			text->setOutlineColor(BLACK);
		}	
	}
	else if (item->getItemType() == STAR) {
		const Star* star = dynamic_cast<const Star*>(item);
		if (star->getStarType() == YELLOW_STAR) {
			eatStar();
			scores += star->getPoint();
			text = new TextEffect(to_string(star->getPoint()).c_str(), Vector2{ getCenterX(), getTop() });
		}
	}
	else if (item->getItemType() == FLOWER) {
		const Flower* flower = dynamic_cast<const Flower*>(item);
		if (flower->getFlowerType() == FIRE_FLOWER) {
			scores += flower->getPoint();
			eatFireFlower();
			text = new TextEffect(to_string(flower->getPoint()).c_str(), Vector2{ getCenterX(), getTop() });
		}
	}
	else if (item->getItemType() == COIN) {
		const Coin* coin = dynamic_cast<const Coin*>(item);
		if (coin->getCoinType() == STATIC_COIN) {
			coins++;
			scores += coin->getPoint();
			text = new TextEffect(to_string(coin->getPoint()).c_str(), Vector2{ getCenterX(), getTop() });
			RESOURCE_MANAGER.playSound("coin.wav");
		}
	}
	if (text != nullptr) {
		globalGameEngine->addEffect(text);
	}
}

void Character::collisionWithEnemy(Enemy* enemy, CollisionType CollType)
{
	if (!enemy) return;
	if (Character_state == STATE_STAR || Character_state == STATE_SUPERSTAR || Character_state == STATE_FIRESTAR) {
		// attacked
		scores += enemy->getScores();
		RESOURCE_MANAGER.playSound("stomp.wav");

		//enemy->attacked(this->direction); for attacked
		enemy->stomped();
		
	}
	else if (enemy->getEnemyType() != SHELL) {
		if (CollType == COLLISION_TYPE_SOUTH && enemy->getEnemyType() != PIRANHA) {
			// stomped
			scores += enemy->getScores();
			setVelY(jet_stomp_velocity);
			setJumping(true);
			RESOURCE_MANAGER.playSound("stomp.wav");
			enemy->stomped();
		}
		else if (countImmortalTime > 0.f)
			return;
		else lostSuit();
	}
	else if (enemy->getEnemyType() == SHELL) {

	}
}

void Character::CollisionWithFireball(FireBall* fireball)
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

void Character::setVictory(bool victory)
{
	this->victory = victory;
}

void Character::eatGreenMushrooms() // +1 health
{
	RESOURCE_MANAGER.playSound("1-up.wav");
	this->lives++;
}

void Character::eatRedMushrooms() // transform to super
{
	RESOURCE_MANAGER.playSound("power_up.wav");
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
	RESOURCE_MANAGER.playSound("power_up.wav");
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
	RESOURCE_MANAGER.playSound("power_up.wav");
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


