// JumpingPiranhaPlant.cpp
#include "../include/JumpingPiranhaPlant.h"
#include "../include/GameEngine.h"

const float JumpingPiranhaPlant::ANIM_INTERVAL = 3.0f;
const float JumpingPiranhaPlant::JUMP_HEIGHT = 150.0f;  

JumpingPiranhaPlant::JumpingPiranhaPlant(Vector2 pos, Texture2D texture)
    : PiranhaPlant(pos, texture)
    , animTimer(0.0f)
{
    baseY = pos.y;
    size = { 32, 42 };
    scores = 200.f;
    UpdateTexture(false);
    piranhaType = JUMPING_PIRANHA;
}

void JumpingPiranhaPlant::Update() {
    Entity::Update();
    if (isDead() || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                dead = true;
            }
        }
        UpdateTexture(true);
        return;
    }

    float dt = GetFrameTime();
    animTimer += dt;
    if (animTimer >= ANIM_INTERVAL) animTimer -= ANIM_INTERVAL;

    // Định nghĩa thời gian cho mỗi giai đoạn
    const float ANTICIPATION_TIME = 1.f; // Thời gian lấy đà
    const float JUMP_TIME = 0.5f;        // Thời gian nhảy lên
    const float FALL_TIME = ANIM_INTERVAL - ANTICIPATION_TIME - JUMP_TIME; // Thời gian rơi xuống

    float phaseTimer = animTimer;
    float yOffset = 0.0f;
    bool isGoingUp = false;

    if (phaseTimer < ANTICIPATION_TIME) {
        // Giai đoạn 1: Lấy đà (hành động "nhảy nhẹ")
        float anticipationPhase = phaseTimer / ANTICIPATION_TIME;
        yOffset = sin(anticipationPhase * 1.5708f * 2) * 5.0f; // Slower frequency, larger amplitude // Tạo hiệu ứng thụt xuống rồi về lại chỗ cũ
        isGoingUp = false;
    }
    else if (phaseTimer < ANTICIPATION_TIME + JUMP_TIME) {
        // Giai đoạn 2: Nhảy lên
        float jumpPhase = (phaseTimer - ANTICIPATION_TIME) / JUMP_TIME;
        float offsetRatio = 1.0f - (1.0f - jumpPhase) * (1.0f - jumpPhase);
        yOffset = offsetRatio * JUMP_HEIGHT;
        isGoingUp = true;
    }
    else {
        // Giai đoạn 3: Rơi xuống
        float fallPhase = (phaseTimer - (ANTICIPATION_TIME + JUMP_TIME)) / FALL_TIME;
        float offsetRatio = 1.0f - (fallPhase * fallPhase);
        yOffset = offsetRatio * JUMP_HEIGHT;
        isGoingUp = false;
    }

    // Cập nhật vị trí y
    position.y = baseY - yOffset;
    Enemy::updateCollision();
    // Cập nhật texture dựa vào phase
    UpdateTexture(isGoingUp);
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
    j["properties"] = json::array({
    {
        { "name", "Name" },
        { "type", "string" },
        { "value", "Enemy" }
    },
    {
        { "name", "Type" },
        { "type", "string" },
        { "value", "JumpingPiranhaPlant"}
    }
        });
}

void JumpingPiranhaPlant::UpdateTexture(bool isGoingUp) {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("PiranhaPlant_JUMP_UP_0");
        return;
    }
    // Tốc độ animation đóng/mở miệng. bạn có thể thay đổi số này.
    const float FRAME_ANIMATION_SPEED = 0.2f;

    frameAcum += GetFrameTime();
    if (frameAcum > FRAME_ANIMATION_SPEED) {
        currFrame = (currFrame + 1) % 2;
        frameAcum = 0.0f;
    }

    const char* key;
    if (isGoingUp) {
        static const char* upKeys[2] = { "PiranhaPlant_JUMP_UP_0", "PiranhaPlant_JUMP_UP_1" };
        key = upKeys[currFrame];
    }
    else {
        static const char* downKeys[2] = { "PiranhaPlant_JUMP_UP_0", "PiranhaPlant_JUMP_DOWN_1" };
        key = downKeys[currFrame];
    }

    // Lấy texture và chỉ gán nếu hợp lệ
    Texture2D newTex = RESOURCE_MANAGER.getTexture(key);
    if (newTex.id != 0) {
        texture = newTex;
    }
}
