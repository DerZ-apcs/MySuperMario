// JumpingPiranhaPlant.cpp
#include "../include/JumpingPiranhaPlant.h"
#include "../include/ResourceManager.h"
#include <raylib.h>

const float JumpingPiranhaPlant::ANIM_INTERVAL = 1.0f;   // 1s cho 1 chu kỳ
const float JumpingPiranhaPlant::JUMP_HEIGHT = 20.0f;  // nhảy cao 20px

JumpingPiranhaPlant::JumpingPiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario)
    : PiranhaPlant(pos, texture, mario)
    , animTimer(0.0f)
{
    baseY = pos.y;
    UpdateTexture();
}

void JumpingPiranhaPlant::Update() {
    float dt = GetFrameTime();
    animTimer += dt;
    if (animTimer >= ANIM_INTERVAL) animTimer -= ANIM_INTERVAL;

    // Tính tỉ lệ trong chu kỳ: 0→1
    float phase = animTimer / ANIM_INTERVAL;
    float offsetRatio;
    if (phase < 0.5f) {
        // nửa đầu: đi lên
        offsetRatio = phase / 0.5f;
    }
    else {
        // nửa sau: đi xuống
        offsetRatio = 1.0f - (phase - 0.5f) / 0.5f;
    }

    // Dịch chuyển y: baseY – (offsetRatio * JUMP_HEIGHT)
    position.y = baseY - offsetRatio * JUMP_HEIGHT;

    // Cập nhật texture dựa vào phase
    UpdateTexture();
}

void JumpingPiranhaPlant::UpdateTexture() {
    // Dùng texture Up trong nửa đầu chu kỳ, Down nửa sau
    const char* key = (animTimer < ANIM_INTERVAL * 0.5f)
        ? TEX_UP
        : TEX_DOWN;
    texture = Singleton<ResourceManager>::getInstance().getTexture(key);
}