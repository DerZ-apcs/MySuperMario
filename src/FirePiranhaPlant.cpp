#include "../include/FirePiranhaPlant.h"
#include "../include/ResourceManager.h"
#include "../include/GameEngine.h"
#include <raylib.h>
#include <raymath.h>

// FirePiranhaPlant Class Implementation
const float FirePiranhaPlant::FIREBALL_INTERVAL = 1.0f; // Bắn fireball mỗi 2s khi trồi lên
const float RapidFirePiranha::FIREBALL_INTERVAL = 0.5f;
const float HomingFirePiranha::FIREBALL_INTERVAL = 0.75f;
const float HomingFirePiranha::DETECTION_RANGE = 300.0f;

FirePiranhaPlant::FirePiranhaPlant(Vector2 pos, Texture2D texture)
    : PiranhaPlant(pos, texture), fireBallTimer(0.0f) {
    size = { 32, 66 };
    frameTime = 0.15f;
    maxFrame = 1;
}

FirePiranhaPlant::~FirePiranhaPlant() {

}

void FirePiranhaPlant::Update() {
    if (isDead() || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                dead = true;
            }
        }
        UpdateTexture();
        return;
    }

    const float deltaTime = GetFrameTime();

    if (invincibilityTimer > 0) {
        invincibilityTimer -= deltaTime;
    }

    if (delayTimer > 0) {
        delayTimer -= deltaTime;
        if (delayTimer <= 0) {
            popUpTimer = 0.0f;
        }
        else {
            position.y = baseY;
            UpdateTexture();
            return;
        }
    }

    popUpTimer += deltaTime;
    float cycleTime = 2 * POP_UP_DURATION + STAY_UP_DURATION;

    if (popUpTimer >= cycleTime) {
        popUpTimer = 0.0f;
        fireBallTimer = 0.0f;
    }

    if (popUpTimer < POP_UP_DURATION) {
        isPoppingUp = true;
        float t = popUpTimer / POP_UP_DURATION;
        position.y = baseY - popUpHeight * t;
    }
    else if (popUpTimer < POP_UP_DURATION + STAY_UP_DURATION) {
        position.y = baseY - popUpHeight;
        fireBallTimer += deltaTime;
        if (fireBallTimer >= FIREBALL_INTERVAL) {
            ShootFireBall();
            fireBallTimer = 0.0f;
        }
    }
    else {
        isPoppingUp = false;
        float t = (popUpTimer - POP_UP_DURATION - STAY_UP_DURATION) / POP_UP_DURATION;
        position.y = baseY - popUpHeight * (1.0f - t);
    }
    Enemy::updateCollision();
    UpdateTexture();
}

void FirePiranhaPlant::draw() {
    PiranhaPlant::draw();
}

void FirePiranhaPlant::UpdateTexture() {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("FirePiranhaPlant_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (currFrame == 0) {
        texture = RESOURCE_MANAGER.getTexture("FirePiranhaPlant_OPEN");
    }
    else {
        texture = RESOURCE_MANAGER.getTexture("FirePiranhaPlant_CLOSED");
    }
}

void FirePiranhaPlant::ShootFireBall() {
    //if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    //Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    //if (!character) return;

    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p && p->getPhase() != CLEARLEVEL_PHASE && p->getPhase() != DEAD_PHASE) {
            Direction dir = (p->getX() > position.x) ? RIGHT : LEFT;
            Vector2 fireBallPos = { position.x, position.y + 10 };
            const int numFireballs = 3;
            const float angleSpread = 15.0f;
            const float baseSpeed = 300.0f;

            for (int i = 0; i < numFireballs; ++i) {
                float angle = (i - (numFireballs - 1) / 2.0f) * angleSpread;
                float rad = angle * DEG2RAD;
                float velX = baseSpeed * cosf(rad) * (dir == RIGHT ? 1.0f : -1.0f);
                float velY = -200.0f + baseSpeed * sinf(rad);
                Vector2 fireBallVel = { velX, velY };
                EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f);
                globalGameEngine->addEnemyFireBall(fireball);
            }
        }
    }
   
    //RESOURCE_MANAGER.playSound("fireball.wav");
}

// RapidFirePiranha Class Implementation
RapidFirePiranha::RapidFirePiranha(Vector2 pos, Texture2D texture)
    : FirePiranhaPlant(pos, texture) {
}

void RapidFirePiranha::ShootFireBall() {
    //if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p && p->getPhase() != CLEARLEVEL_PHASE && p->getPhase() != DEAD_PHASE) {
            Direction dir = (p->getX() > position.x) ? RIGHT : LEFT;
            Vector2 fireBallPos = { position.x, position.y + 10 };
            Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 200.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
            EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f);
            globalGameEngine->addEnemyFireBall(fireball);
        }
    }
    RESOURCE_MANAGER.playSound("fireball.wav");
}

HomingFirePiranha::HomingFirePiranha(Vector2 pos, Texture2D texture)
    : FirePiranhaPlant(pos, texture) {
}

void HomingFirePiranha::ShootFireBall() {
    //if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn

    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p && p->getPhase() != CLEARLEVEL_PHASE && p->getPhase() != DEAD_PHASE) {
            Direction dir = (p->getX() > position.x) ? RIGHT : LEFT;
            Vector2 fireBallPos = { position.x, position.y + 10 };
            Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 200.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
            bool isHoming = false;
            float distanceToMario = Vector2Distance(position, p->getPosition());
            if (distanceToMario <= DETECTION_RANGE) {
                isHoming = true; // Kích hoạt nhắm mục tiêu khi Mario ở gần
            }
            EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, isHoming);
            globalGameEngine->addEnemyFireBall(fireball);
        }
    }
    RESOURCE_MANAGER.playSound("fireball.wav");
}