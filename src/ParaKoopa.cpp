// ParaKoopa.cpp
#include "../include/ParaKoopa.h"
#include "../include/ResourceManager.h"
#include "../include/GameEngine.h"

static constexpr float RED_JUMP_INTERVAL = 2.5f;
static constexpr float RED_JUMP_VELOCITY = 250.0f;
static constexpr float RED_RUN_SPEED = 80.0f;

static constexpr float BLUE_JUMP_INTERVAL = 1.2f;
static constexpr float BLUE_JUMP_VELOCITY = 180.0f;
static constexpr float BLUE_RUN_SPEED = 40.0f;

static constexpr float GREEN_JUMP_INTERVAL = 3.0f;
static constexpr float GREEN_JUMP_VELOCITY = 300.0f;
static constexpr float GREEN_RUN_SPEED = 60.0f;

static constexpr float YELLOW_JUMP_INTERVAL = 2.0f;
static constexpr float YELLOW_JUMP_VELOCITY = 400.0f;
static constexpr float YELLOW_RUN_SPEED = 50.0f;

ParaKoopa::ParaKoopa(Vector2 pos, Texture2D texture)
	: Koopa(pos, texture), jumpTimer(0.0f),
	hasWings(true)
    //paraKoopaType(RED_PARAKOOPA)
{
	isKicked = false;
	//koopaType = RED_KOOPA; // Default type, can be changed in derived classes
	direction = LEFT; // Default direction, can be changed later
	velocity = (direction == LEFT) ? Vector2{ -RED_RUN_SPEED, 0.0f } : Vector2{ RED_RUN_SPEED, 0.0f };
	frameTime = 0.15f;
	maxFrame = 1;
	currFrame = 0;
	frameAcum = 0.0f;
	isFlipped = false;
	size = { 32, 56 };
    scores = SCORE_STOMP_KOOPA;
	UpdateTexture();
	updateCollision();
}

float ParaKoopa::getScores() const
{
    return scores;
}

ENEMY_TYPE ParaKoopa::getEnemyType() const
{
	if (koopaState == SHELL_KOOPA)
		return SHELL;
	return PARAKOOPA;
}

void ParaKoopa::Update()
{
	if (!hasWings) {
		Koopa::Update();
		return;
	}
	const float deltaTime = GetFrameTime();
	Entity::Update();
	if (isReadyForRemoval() || state == STATE_IS_DYING) {
		Enemy::Update();
		return;
	}
	if (collisionTimer > 0) {
		collisionTimer -= deltaTime;
	}
	/*if (velocity.y > 50) {
		state = FALLING;
	}*/
	if (isOnGround()) {
		velocity.y = 0;
		state = ON_GROUND;
		jumpTimer += deltaTime;
	}
	if (getGravityAvailable()) {
		velocity.y += GRAVITY * deltaTime;
	}
	position.y += velocity.y * deltaTime;
	position.x += velocity.x * deltaTime;
	updateCollision();
	UpdateTexture();
}

void ParaKoopa::draw()
{
	if (!hasWings) {
		Koopa::draw();
		return;
	}
	DrawTexture(texture, position.x, position.y, WHITE);
	if (SETTING.getDebugMode()) {
		CollNorth.draw();
		CollSouth.draw();
		CollEast.draw();
		CollWest.draw();
	}
}

void ParaKoopa::UpdateTexture()
{

}

void ParaKoopa::stomped()
{
	if (isReadyForRemoval() || state == STATE_IS_DYING) return;
	if (hasWings) {
		hasWings = false;
		position.y += 2;
		size = { 32, 54 };
		velocity.y = 0;
		velocity.x = (direction == LEFT) ? -KOOPA_SPEED : KOOPA_SPEED;
		state = FALLING;
		setGravityAvailable(true);
		if (SETTING.isSoundEnabled()) {
			RESOURCE_MANAGER.playSound("stomp.wav");
		}
	}
	else {
		Koopa::stomped();
	}
}

void ParaKoopa::CollisionWithFireball(FireBall* fireball)
{
	fireball->setEntityDead();
	SmokeEffect* smokeright = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ 60, 120 });
	globalGameEngine->addEffect(smokeright);
	SmokeEffect* smokeleft = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ -60, 120 });
	globalGameEngine->addEffect(smokeleft);
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
	stomped();
}

void ParaKoopa::loadEntity(const json& j)
{
    Koopa::loadEntity(j);
    jumpTimer = j["jumpTimer"];
    paraKoopaType = static_cast<PARAKOOPA_TYPE>(j["paraKoopaType"].get<int>());
}

void ParaKoopa::saveEntity(json& j) const
{
    Koopa::saveEntity(j);
    j["jumpTimer"] = jumpTimer;
    j["paraKoopaType"] = static_cast<int>(paraKoopaType);
}

ParaKoopaRed::ParaKoopaRed(Vector2 pos, Texture2D texture) : ParaKoopa(pos, texture) {
    paraKoopaType = RED_PARAKOOPA;
	koopaType = RED_KOOPA;
	velocity = (direction == LEFT) ? Vector2{ -RED_RUN_SPEED, 0.0f } : Vector2{ RED_RUN_SPEED, 0.0f };
}

void ParaKoopaRed::Update() {
	ParaKoopa::Update();
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > RED_JUMP_INTERVAL) {
        velocity.y = -RED_JUMP_VELOCITY;
		state = JUMPING;
        jumpTimer = 0.0f;
    }
}

void ParaKoopaRed::UpdateTexture()
{
	if (!hasWings) {
		Koopa::UpdateTexture();
		return;
	}
	std::string paraKoopaTypeStr = "Red";
	frameAcum += GetFrameTime();
	if (frameAcum > frameTime) {
		currFrame = (currFrame + 1) % (maxFrame + 1);
		frameAcum = 0;
	}
	if (direction == LEFT) {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_LEFT_" + std::to_string(currFrame));
	}
	else {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_RIGHT_" + std::to_string(currFrame));
	}
}

void ParaKoopaRed::saveEntity(json& j) const
{
	ParaKoopa::saveEntity(j);
	j["properties"] = json::array({
	{
		{ "name", "Name" },
		{ "type", "string" },
		{ "value", "Enemy" }
	},
	{
		{ "name", "Type" },
		{ "type", "string" },
		{ "value", "ParaKoopaRed"}
	}
		});
}

ParaKoopaBlue::ParaKoopaBlue(Vector2 pos, Texture2D texture)
    : ParaKoopa(pos, texture) {
    paraKoopaType = BLUE_PARAKOOPA;
	koopaType = BLUE_KOOPA;
	velocity = (direction == LEFT) ? Vector2{ -BLUE_RUN_SPEED, 0.0f } : Vector2{ BLUE_RUN_SPEED, 0.0f };

}

void ParaKoopaBlue::Update() {
	ParaKoopa::Update();
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > BLUE_JUMP_INTERVAL) {
        velocity.y = -BLUE_JUMP_VELOCITY;
 	    state = JUMPING;
        jumpTimer = 0.0f;
    }
}

void ParaKoopaBlue::UpdateTexture()
{
	if (!hasWings) {
		Koopa::UpdateTexture();
		return;
	}
	std::string paraKoopaTypeStr = "Blue";
	frameAcum += GetFrameTime();
	if (frameAcum > frameTime) {
		currFrame = (currFrame + 1) % (maxFrame + 1);
		frameAcum = 0;
	}
	if (direction == LEFT) {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_LEFT_" + std::to_string(currFrame));
	}
	else {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_RIGHT_" + std::to_string(currFrame));
	}
}

void ParaKoopaBlue::saveEntity(json& j) const
{
	ParaKoopa::saveEntity(j);
	j["properties"] = json::array({
	{
		{ "name", "Name" },
		{ "type", "string" },
		{ "value", "Enemy" }
	},
	{
		{ "name", "Type" },
		{ "type", "string" },
		{ "value", "ParaKoopaBlue"}
	}
		});
}

ParaKoopaGreen::ParaKoopaGreen(Vector2 pos, Texture2D texture):
    ParaKoopa(pos, texture)
{
    paraKoopaType = GREEN_PARAKOOPA;
	koopaType = GREEN_KOOPA;
	velocity = (direction == LEFT) ? Vector2{ -GREEN_RUN_SPEED, 0.0f } : Vector2{ GREEN_RUN_SPEED, 0.0f };
}

void ParaKoopaGreen::Update()
{
	ParaKoopa::Update();
	jumpTimer += GetFrameTime();
	if (state == ON_GROUND && jumpTimer > GREEN_JUMP_INTERVAL) {
		velocity.y = -GREEN_JUMP_VELOCITY;
		state = JUMPING;
		jumpTimer = 0.0f;
	}
}

void ParaKoopaGreen::UpdateTexture()
{
	if (!hasWings) {
		Koopa::UpdateTexture();
		return;
	}
	std::string paraKoopaTypeStr = "Green";
	frameAcum += GetFrameTime();
	if (frameAcum > frameTime) {
		currFrame = (currFrame + 1) % (maxFrame + 1);
		frameAcum = 0;
	}
	if (direction == LEFT) {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_LEFT_" + std::to_string(currFrame));
	}
	else {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_RIGHT_" + std::to_string(currFrame));
	}
}

void ParaKoopaGreen::saveEntity(json& j) const
{
	ParaKoopa::saveEntity(j);
	j["properties"] = json::array({
	{
		{ "name", "Name" },
		{ "type", "string" },
		{ "value", "Enemy" }
	},
	{
		{ "name", "Type" },
		{ "type", "string" },
		{ "value", "ParaKoopaGreen"}
	}
		});
}


ParaKoopaYellow::ParaKoopaYellow(Vector2 pos, Texture2D texture):
    ParaKoopa(pos, texture)
{
    paraKoopaType = YELLOW_PARAKOOPA;
	koopaType = YELLOW_KOOPA;
	velocity = (direction == LEFT) ? Vector2{ -YELLOW_RUN_SPEED, 0.0f } : Vector2{ YELLOW_RUN_SPEED, 0.0f };
}

void ParaKoopaYellow::Update()
{
	ParaKoopa::Update();

	jumpTimer += GetFrameTime();
	if (state == ON_GROUND && jumpTimer > YELLOW_JUMP_INTERVAL) {
		velocity.y = -YELLOW_JUMP_VELOCITY;
		state = JUMPING;
		jumpTimer = 0.0f;
	}
}

void ParaKoopaYellow::UpdateTexture()
{
	if (!hasWings) {
		Koopa::UpdateTexture();
		return;
	}
	std::string paraKoopaTypeStr = "Yellow";
	frameAcum += GetFrameTime();
	if (frameAcum > frameTime) {
		currFrame = (currFrame + 1) % (maxFrame + 1);
		frameAcum = 0;
	}
	if (direction == LEFT) {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_LEFT_" + std::to_string(currFrame));
	}
	else {
		texture = RESOURCE_MANAGER.getTexture("ParaKoopa" + paraKoopaTypeStr + "_RIGHT_" + std::to_string(currFrame));
	}
}

void ParaKoopaYellow::saveEntity(json& j) const
{
	ParaKoopa::saveEntity(j);
	j["properties"] = json::array({
	{
		{ "name", "Name" },
		{ "type", "string" },
		{ "value", "Enemy" }
	},
	{
		{ "name", "Type" },
		{ "type", "string" },
		{ "value", "ParaKoopaYellow"}
	}
		});
}
