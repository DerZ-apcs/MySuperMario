#include "../include/Enemy.h"
#include "../include/Mario.h"
#include "../include/GameEngine.h"
#include <raylib.h>
#include <raymath.h>
#include <SmokeEffect.h>

// Enemy Class Implementation
Enemy::Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction direction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color)
    : Entity(pos, size, vel, direction, state, frameTime, maxFrame, color), deathTimer(0.0f), squashScale(1.0f), isFlipped(false), isKicked(false)
{
    CollNorth.setSize({ size.x / 2, 5 });
    CollSouth.setSize({ size.x / 2, 5 });
    CollWest.setSize({ 5, size.y - 5 });
    CollEast.setSize({ 5, size.y - 5 });
    CollEast.setColor(BLACK);
    CollSouth.setColor(GREEN);
    CollNorth.setColor(RED);
    CollWest.setColor(PURPLE);
}

Enemy::~Enemy() {
}

void Enemy::stomped()
{
    // old CollsionWithCharacter
}


void Enemy::Update() {
    if (isDead() || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                dead = true; // Mark for removal
            }
        }
        UpdateTexture();
        return;
    }
    const float deltaTime = GetFrameTime();
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    if (getGravityAvailable())
        velocity.y += GRAVITY * deltaTime;
    if (velocity.y > 20) state = FALLING;
    if (state != ON_GROUND) {
        if (velocity.y > 0 && state == JUMPING) {
            state = FALLING;
        }
    }
    updateCollision();
}

void Enemy::draw() {
    if (!isDead()) {
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        if (isFlipped) {
            source.width *= -1; // Lật ngược texture
        }
        DrawTexturePro(texture, source, { position.x, position.y, size.x, size.y }, { 0.f, 0.f }, 0.f, WHITE);
        
        if (SETTING.getDebugMode()) {
            CollNorth.draw();
            CollSouth.draw();
            CollEast.draw();
            CollWest.draw();
        }
    }
}

void Enemy::updateSquashEffect() {
    if (state == STATE_IS_DYING) {
        squashScale = 1.0f - (ENEMY_DEATH_TIMER_DEFAULT - deathTimer) / ENEMY_DEATH_TIMER_DEFAULT; // Thu nhỏ chiều dọc
        updateCollision();
        isFlipped = true; // Lật ngược khi đang chết
        updateCollision();
    }
}

void Enemy::CollisionWithFireball(FireBall* fireball) {
    if (!isDead() && state != STATE_IS_DYING && !fireball->isDead()) {
        fireball->setEntityDead();
        state = STATE_IS_DYING;
        //if (getEnemyType() == BOBOMB) {

        //}
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        velocity.y = -250; // Nhảy lên nhẹ
        velocity.x = (rand() % 100) - 50; // Văng ngang ngẫu nhiên
        updateCollision();
        if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomped.wav");
        // text effect
        Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_GOOMBA).c_str()), Vector2{this->getCenterX(), this->getTop()});
        globalGameEngine->addEffect(score);
        SmokeEffect* smokeright = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ 60, 120 });
        globalGameEngine->addEffect(smokeright);
        SmokeEffect* smokeleft = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ -60, 120 });
        globalGameEngine->addEffect(smokeleft);
    }
}

EntityType Enemy::getEntityType() const
{
    return ENEMY;
}

bool Enemy::isDying() {
    return dead || state == STATE_IS_DYING;
}

bool Enemy::isReadyForRemoval() {
    return dead;
}

void Enemy::updateCollision() {
    CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y });
    CollSouth.setPos({ position.x + size.x / 2 - CollSouth.getWidth() / 2, position.y + size.y * squashScale - CollSouth.getHeight() });
    CollEast.setPos({ position.x + size.x * squashScale - CollEast.getWidth(), position.y + size.y * squashScale / 2 - CollEast.getHeight() / 2 });
    CollWest.setPos({ position.x, position.y + size.y * squashScale / 2 - CollWest.getHeight() / 2 });
}

void Enemy::kicked(Direction direction)
{ 
    // for koopa shell only
}

bool Enemy::getIsKicked() const
{
    return isKicked;
}

void Enemy::setIsKicked(bool isKicked)
{
    this->isKicked = isKicked;
}

void Enemy::UpdateTexture() {
    // Virtual method, implemented in derived classes
}


void Enemy::attacked(Direction direction) {
    if (isDead()) return;
    setEntityDead();
    //this->isdead = true;
    setCollisionAvailable(false);
}

float Enemy::getScores() const
{
    return scores;
}

void Enemy::setCollisionTimer(float time)
{
    collisionTimer = time;
}

void Enemy::setDeathTimer(float time)
{
    deathTimer = time;
}
