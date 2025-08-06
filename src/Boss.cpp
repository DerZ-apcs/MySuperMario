#include "../include/Boss.h"

Boss::Boss(Vector2 pos, Vector2 size, Texture2D initialTexture, int hp)
    : Enemy(pos, size, { 0,0 }, LEFT, ON_GROUND, initialTexture, 0.1f, 1, WHITE),
    maxHp(hp), currentHp(hp), vulnerable(true), stateTimer(0.0f) {
}

void Boss::takeDamage(int amount) {
    if (!vulnerable || isDying()) return;
    currentHp -= amount;
    if (currentHp <= 0) {
        die();
    }
    else {
        onHit();
    }
}

void Boss::die() {
    setDeathTimer(ENEMY_DEATH_TIMER_LONG);
    vulnerable = false;
    setCollisionAvailable(false);
    onDeath();
}

void Boss::onDeath() {

}

void Boss::onHit() {

}

void Boss::Update() {
    if (isDying() || isReadyForRemoval()) {
        Enemy::Update();
        return;
    }
    updateBehavior();
	UpdateTexture();
    applyPhysics();
    updateCollision();
    Enemy::Update();
}

void Boss::applyPhysics() {
    float dt = GetFrameTime();
    position.y += velocity.y * dt;
    if (getGravityAvailable()) velocity.y += GRAVITY * dt;
}

void Boss::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
    maxHp = j["maxHp"];
    currentHp = j["currentHp"];
    vulnerable = j["vulnerable"];
    stateTimer = j["stateTimer"];
}

void Boss::saveEntity(json& j) const
{
    Enemy::saveEntity(j);
    j["maxHp"] = maxHp;
    j["currentHp"] = currentHp;
    j["vulnerable"] = vulnerable;
    j["stateTimer"] = stateTimer;
}
