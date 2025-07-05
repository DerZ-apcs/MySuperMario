#include "../include/FirePiranhaPlant.h"
#include "../include/ResourceManager.h"
#include <raylib.h>
#include <raymath.h>

// FirePiranhaPlant Class Implementation
const float FirePiranhaPlant::FIREBALL_INTERVAL = 0.5f; // Bắn fireball mỗi 2s khi trồi lên

FirePiranhaPlant::FirePiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario)
    : PiranhaPlant(pos, texture, mario), fireBallTimer(0.0f) {
    size = { 32, 48 };
    frameTime = 0.15f;
    maxFrame = 1;
}

FirePiranhaPlant::~FirePiranhaPlant() {
    for (auto fireball : fireballs) {
        delete fireball;
    }
    fireballs.clear();
}

void FirePiranhaPlant::Update() {
    if (isDead || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                isDead = true;
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
            UpdatePhysics();
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

    for (auto fireball : fireballs) {
        if (!fireball->IsDestroyed()) {
            fireball->Update();
        }
    }

    fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](EnemyFireBall* fireball) {
        if (fireball && (fireball->isMaxDistance() || fireball->IsDestroyed())) {
            delete fireball;
            return true;
        }
        return false;
        }), fireballs.end());

    UpdatePhysics();
    UpdateTexture();
}

void FirePiranhaPlant::draw() {
    if (isDead || isReadyForRemoval()) {
        return;
    }

    float emergedHeight = baseY - position.y;
    if (emergedHeight <= 0) {
        return;
    }

    if (emergedHeight > popUpHeight) {
        emergedHeight = popUpHeight;
    }

    Rectangle source = { 0.0f, (float)texture.height - emergedHeight - 10, (float)texture.width, emergedHeight };
    Rectangle dest = { position.x, position.y, (float)texture.width * squashScale, emergedHeight * squashScale };
    Vector2 origin = { (texture.width * squashScale) / 2, 0 };
    DrawTexturePro(texture, source, dest, origin, 0.1f, WHITE);

    for (auto fireball : fireballs) {
        if (!fireball->IsDestroyed()) {
            fireball->draw();
        }
    }

#ifdef DEBUG
    if (emergedHeight >= CollNorth.getHeight()) {
        CollNorth.draw();
    }
    if (emergedHeight >= CollSouth.getHeight()) {
        CollSouth.draw();
    }
    if (emergedHeight >= CollEast.getHeight()) {
        CollEast.draw();
    }
    if (emergedHeight >= CollWest.getHeight()) {
        CollWest.draw();
    }
#endif
}

void FirePiranhaPlant::UpdateTexture() {
    if (isDead || state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("FirePiranhaPlant_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (currFrame == 0) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("FirePiranhaPlant_OPEN");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture("FirePiranhaPlant_CLOSED");
    }
}

void FirePiranhaPlant::ShootFireBall() {
    Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x, position.y + 10 };
    Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 400.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f);
    fireballs.push_back(fireball);
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL");
}

std::list<EnemyFireBall*>* FirePiranhaPlant::getFireBalls() {
    return &fireballs;
}