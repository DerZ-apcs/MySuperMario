// JumpingPiranhaPlant.cpp
#include "../include/JumpingPiranhaPlant.h"
#include "../include/GameEngine.h"

const float JumpingPiranhaPlant::ANIM_INTERVAL = 1.0f;   // 1s cho 1 chu kỳ
const float JumpingPiranhaPlant::JUMP_HEIGHT = 20.0f;  // nhảy cao 20px

JumpingPiranhaPlant::JumpingPiranhaPlant(Vector2 pos, Texture2D texture)
    : PiranhaPlant(pos, texture)
    , animTimer(0.0f)
{
    baseY = pos.y;
    size = { 32, 42 };
    scores = 200.f;
    UpdateTexture(true);
    piranhaType = JUMPING_PIRANHA;
}

void JumpingPiranhaPlant::Update() {
    float dt = GetFrameTime();
    animTimer += dt;
    if (animTimer >= ANIM_INTERVAL) animTimer -= ANIM_INTERVAL;

    // Tính tỉ lệ trong chu kỳ: 0→1
    float phase = animTimer / ANIM_INTERVAL;
    float offsetRatio;
    bool isGoingUp;
    if (phase < 0.5f) {
        // nửa đầu: đi lên
        offsetRatio = phase / 0.5f;
        isGoingUp = true;
    }
    else {
        // nửa sau: đi xuống
        offsetRatio = 1.0f - (phase - 0.5f) / 0.5f;
        isGoingUp = false;
    }
	position.y = velocity.y * dt; 
	velocity.y += GRAVITY * dt; 

    // Dịch chuyển y: baseY – (offsetRatio * JUMP_HEIGHT)
    position.y = baseY - offsetRatio * JUMP_HEIGHT;
    Enemy::updateCollision();
    // Cập nhật texture dựa vào phase
    UpdateTexture(isGoingUp);
}

void JumpingPiranhaPlant::stomped()
{
    if (isDead() || state == STATE_IS_DYING || invincibilityTimer > 0) return;
    state = STATE_IS_DYING;
    velocity.x = 0;
    velocity.y = 0;
    deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
    invincibilityTimer = 0.5f;
    updateSquashEffect();
    Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_REX).c_str()), getCenter());
    globalGameEngine->addEffect(score);
}

void JumpingPiranhaPlant::loadEntity(const json& j)
{
    PiranhaPlant::loadEntity(j);
    animTimer = j["animTimer"];
}

void JumpingPiranhaPlant::saveEntity(json& j) const
{
    PiranhaPlant::saveEntity(j);
    j["animTimer"] = animTimer;
}

void JumpingPiranhaPlant::UpdateTexture(bool isGoingUp) {
    // Dùng texture Up trong nửa đầu chu kỳ, Down nửa sau
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % 2;
        frameAcum = 0.0f;
    }
    const char* key;
    if (isGoingUp) {
        static const char* upKeys[2] = { "PiranhaPlant_JUMP_UP_0",   "PiranhaPlant_JUMP_UP_1" };
        key = upKeys[currFrame];
    }
    else {
        static const char* downKeys[2] = { "PiranhaPlant_JUMP_DOWN_0", "PiranhaPlant_JUMP_DOWN_1" };
        key = downKeys[currFrame];
    }

    // 3) Lấy texture và chỉ gán nếu valid
    Texture2D newTex = RESOURCE_MANAGER.getTexture(key);
    if (newTex.id != 0) {
        texture = newTex;
    }
}
