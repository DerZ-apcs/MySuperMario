// Spiny.cpp
#include "../include/Spiny.h"
#include "../include/GameEngine.h"

const int Spiny::SCORE_STOMP_SPINY = 100.f;

Spiny::Spiny(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 32 }, { 0,0 }, LEFT, ON_GROUND, texture, 0.2f, 1, WHITE)
{
	texture = RESOURCE_MANAGER.getTexture("Spiny_LEFT_0");
    updateCollision();
    frameTime = 0.1f;
}

void Spiny::Update() {
    // Nếu đang die animation, dùng logic base để đếm timer và squash
    const float deltaTime = GetFrameTime();
    Entity::Update();
    if (isDying() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    if (state == ON_GROUND) {
        velocity.x = (direction == LEFT ? -SPINY_SPEED : SPINY_SPEED);
	}
    //Enemy::Update();

    if (getGravityAvailable())
        velocity.y += GRAVITY * deltaTime;
    if (velocity.y > 20) state = FALLING;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    Entity::updateCollision();
    UpdateTexture();
}

void Spiny::draw() {
    Enemy::draw();
}

void Spiny::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Spiny_DEAD");
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % 2;
        frameAcum = 0;
    }
    std::string dir = (direction == LEFT ? "LEFT" : "RIGHT");
    if (state == ON_GROUND) {
        texture = RESOURCE_MANAGER.getTexture("Spiny_" + dir + "_" + std::to_string(currFrame));
	}
	else if (state == FALLING || state == JUMPING) {
		texture = RESOURCE_MANAGER.getTexture("Spiny_DEAD");
	}
}

void Spiny::stomped() {
    // only be attacked by state star or fireball
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    state = STATE_IS_DYING;
    velocity.y = -300; // Slight upward bounce
    velocity.x = (rand() % 100) - 50; // Random horizontal velocity
    deathTimer = ENEMY_DEATH_TIMER_LONG; // Disappear after 0.5s
    Effect* text = new TextEffect(to_string(SCORE_STOMP_SPINY).c_str(), getCenter());
    globalGameEngine->addEffect(text);
}

ENEMY_TYPE Spiny::getEnemyType() const
{
    return SPINY;
}

float Spiny::getScores() const
{
    return SCORE_STOMP_SPINY;
}
