#include "../include/FirePiranhaPlant.h"
#include "../include/ResourceManager.h"
#include <raylib.h>
#include <raymath.h>

// FirePiranhaPlant Class Implementation
const float FirePiranhaPlant::FIREBALL_INTERVAL = 1.0f; 
const float RapidFirePiranha::FIREBALL_INTERVAL = 0.5f;
const float HomingFirePiranha::FIREBALL_INTERVAL = 0.75f;
const float HomingFirePiranha::DETECTION_RANGE = 300.0f;

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
    PiranhaPlant::draw();
    for (auto fireball : fireballs) {
        if (!fireball->IsDestroyed()) {
            fireball->UpdateTexture();
            fireball->draw();
        }
    }
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
    if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x, position.y + 10 };
    const int numFireballs = 3;
    const float angleSpread = 15.0f;
    const float baseSpeed = 400.0f;

    for (int i = 0; i < numFireballs && fireballs.size() < MAX_FIREBALLS; ++i) {
        float angle = (i - (numFireballs - 1) / 2.0f) * angleSpread;
        float rad = angle * DEG2RAD;
        float velX = baseSpeed * cosf(rad) * (dir == RIGHT ? 1.0f : -1.0f);
        float velY = -200.0f + baseSpeed * sinf(rad);
        Vector2 fireBallVel = { velX, velY };
        EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, &mario, false);
        fireballs.push_back(fireball);
    }
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL");
}

std::list<EnemyFireBall*>* FirePiranhaPlant::getFireBalls() {
    return &fireballs;
}

// RapidFirePiranha Class Implementation
RapidFirePiranha::RapidFirePiranha(Vector2 pos, Texture2D texture, Mario& mario)
    : FirePiranhaPlant(pos, texture, mario) {
}

void RapidFirePiranha::ShootFireBall() {
    if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x, position.y + 10 };
    Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 400.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f);
    fireballs.push_back(fireball);
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL");
}

HomingFirePiranha::HomingFirePiranha(Vector2 pos, Texture2D texture, Mario& mario)
    : FirePiranhaPlant(pos, texture, mario) {
}

void HomingFirePiranha::ShootFireBall() {
    if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    //Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    //Vector2 fireBallPos = { position.x, position.y + 10 };
    //Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 400.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
    //bool isHoming = false;
    //float distanceToMario = Vector2Distance(position, mario.getPosition());
    //if (distanceToMario <= DETECTION_RANGE) {
    //    isHoming = true; // Kích hoạt nhắm mục tiêu khi Mario ở gần
    //}
    //EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, &mario, isHoming);
    //fireballs.push_back(fireball);
    //Singleton<ResourceManager>::getInstance().playSound("FIREBALL");

    float distanceToMario = Vector2Distance(position, mario.getPosition());
    if (distanceToMario > DETECTION_RANGE) return; // Chỉ bắn khi Mario trong tầm

    Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x, position.y + 10 };

    // Tính toán vector hướng tới vị trí của Mario tại thời điểm bắn
    Vector2 targetPos = mario.getPosition();
    Vector2 directionToMario = Vector2Subtract(targetPos, fireBallPos);
    Vector2 normalizedDirection = Vector2Normalize(directionToMario);

    // Đặt tốc độ cho quả cầu lửa
    const float fireBallSpeed = 400.0f;
    Vector2 fireBallVel = Vector2Scale(normalizedDirection, fireBallSpeed);

    // Tạo quả cầu lửa với isHoming = false để nó không bám theo Mario
    bool isHoming = false;
    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, nullptr, isHoming);

    fireballs.push_back(fireball);
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL");
}