#include "../include/Muncher.h"
#include "../include/GameEngine.h"

Muncher::Muncher(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 30 }, { 0, 0 }, RIGHT, ON_GROUND, texture, 0.25f, 1, DARKGREEN) {
    velocity = { 0, 0 };
    this->texture = RESOURCE_MANAGER.getTexture("Muncher_1");
}

void Muncher::Update() {
    Entity::Update();
    Enemy::Update();
    UpdateTexture();  
}

void Muncher::draw() {
    Enemy::draw();
}

void Muncher::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Muncher_1");
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum >= frameTime) {
        frameAcum -= frameTime;
        currFrame = (currFrame + 1) % (maxFrame + 1);
    }

    texture = RESOURCE_MANAGER.getTexture("Muncher_" + to_string(currFrame));
}

void Muncher::stomped()
{
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    state = STATE_IS_DYING;
    deathTimer = 0.3f;
    updateSquashEffect();
    UpdateTexture();
    Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_GOOMBA).c_str()), getCenter());
    globalGameEngine->addEffect(score);
}


ENEMY_TYPE Muncher::getEnemyType() const {
    return MUNCHER;
}

void Muncher::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
}

void Muncher::saveEntity(json& j) const
{
    Enemy::saveEntity(j);

    // Add Tiled-compatible properties array
    j["properties"] = json::array({
        {
            { "name", "Name" },
            { "type", "string" },
            { "value", "Enemy" }
        },
        {
            { "name", "Type" },
            { "type", "string" },
            { "value", "Muncher"}
        }
        });
}

float Muncher::getScores() const {
    return SCORE_STOMP_MUNCHER;
}

void Muncher::CollisionWithFireball(FireBall* fireball) {
    fireball->setEntityDead();
    if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
    SmokeEffect* smokeright = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ 60, 120 });
    globalGameEngine->addEffect(smokeright);
    SmokeEffect* smokeleft = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ -60, 120 });
    globalGameEngine->addEffect(smokeleft);
}