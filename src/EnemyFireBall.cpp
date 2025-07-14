#include "../include/EnemyFireBall.h"
#include "../include/ResourceManager.h"
#include "../include/Game.h"
#include "../include/GameEngine.h"
#include <raymath.h>

const float EnemyFireBall::maxTime = 2.5f;
const float EnemyFireBall::FB_SpeedX = 400.0f;

EnemyFireBall::EnemyFireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan, bool homing)
    : Entity(pos, sz, vel, dir, ON_GROUND, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), isHoming(homing), currTime(0.f) {
    this->texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("FlowerMarioFireball_RIGHT_0") :
        RESOURCE_MANAGER.getTexture("EnemyFireball_LEFT_0");
    this->frameAcum = 0;
    this->currFrame = 0;
    this->CollNorth.setSize(Vector2{ size.x - 8, 1 });
    this->CollSouth.setSize(Vector2{ size.x - 8, 1 });
    this->CollEast.setSize(Vector2{ 1, size.y - 8 });
    this->CollWest.setSize(Vector2{ 1, size.y - 8 });
    this->updateCollision();
}

EnemyFireBall::~EnemyFireBall() {
}


void EnemyFireBall::Update() {
    if (isMaxTime() || isDead()) return;

    const float deltaTime = GetFrameTime();
    frameAcum += deltaTime;
    currTime += deltaTime;
    maxFrame = 3;
    if (frameAcum >= frameTime) {
        frameAcum = 0;
        currFrame = (currFrame + 1) % (maxFrame + 1);
    }
    timeSpanAcum += deltaTime;
    Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    if (isHoming && character != nullptr) {
        Vector2 toMario = Vector2Subtract(character->getPosition(), position);
        float homingStrength = 0.1f; // Sức mạnh nhắm mục tiêu
        Vector2 targetVel = Vector2Scale(Vector2Normalize(toMario), FB_SpeedX);
        velocity = Vector2Lerp(velocity, targetVel, homingStrength);
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    velocity.y += GRAVITY * deltaTime;

    if (velocity.x > 0) direction = RIGHT;
    else if (velocity.x < 0) direction = LEFT;

    updateCollision();
    UpdateTexture();
}

void EnemyFireBall::draw() {
    if (isMaxTime() || isDead()) return;
    DrawTexture(texture, position.x, position.y, WHITE);
}

void EnemyFireBall::updateCollision() {
    Entity::updateCollision();
}

void EnemyFireBall::UpdateTexture() {
    const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
    std::string textureName = "EnemyFireball" + dir + std::to_string(currFrame);
    texture = RESOURCE_MANAGER.getTexture(textureName);
}

bool EnemyFireBall::isMaxTime() const
{
    return currTime > maxTime;
}

EntityType EnemyFireBall::getEntityType() const
{
    return ENEMY_FIREBALL;
}
