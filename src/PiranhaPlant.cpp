#include "../include/PiranhaPlant.h"
#include "../include/GameEngine.h"

// PiranhaPlant Class Implementation
const float PiranhaPlant::POP_UP_DURATION = 1.5f; // Thời gian trồi lên/rút xuống
const float PiranhaPlant::STAY_UP_DURATION = 1.5f; // Thời gian ở trạng thái trồi lên
const float PiranhaPlant::DURATION_BETWEEN_POPUP = 1.f; // rest between two pops up;

PiranhaPlant::PiranhaPlant(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 66 }, { 0, 0 }, RIGHT, ON_GROUND, texture, 0.2f, 1, RED),
    popUpTimer(0.0f), isPoppingUp(true), popUpHeight(66.0f), baseY(pos.y), delayTimer(0.2f), invincibilityTimer(0.0f),
    piranhaType(NORMAL_PIRANHA)
{ 
    gravityAvailable = true;
    scores = 200.f;
}

PIRANHA_TYPE PiranhaPlant::getPiranhaType() const
{
    return NORMAL_PIRANHA;
}

void PiranhaPlant::Update() {
    Entity::Update();

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

    // Xử lý độ trễ trước khi trồi lên
    if (delayTimer > 0) {
        delayTimer -= deltaTime;
        if (delayTimer <= 0) {
            popUpTimer = 0.0f; // Bắt đầu chu kỳ trồi lên sau độ trễ
        }
        else {
            position.y = baseY; // Giữ ẩn trong ống trong độ trễ
            UpdateTexture();
            return;
        }
    }

    // Thực hiện chu kỳ trồi/rút mà không phụ thuộc vào vị trí Mario
    popUpTimer += deltaTime;

    // Tổng chu kỳ: trồi lên (1s) + ở trên (2s) + rút xuống (1s) = 4s
    float cycleTime = 2 * POP_UP_DURATION + STAY_UP_DURATION;

    if (popUpTimer >= cycleTime) {
        popUpTimer = 0.0f; // Reset chu kỳ
    }

    // Xác định giai đoạn trong chu kỳ
    if (popUpTimer < POP_UP_DURATION) {
        // Giai đoạn trồi lên
        isPoppingUp = true;
        float t = popUpTimer / POP_UP_DURATION; // Tỷ lệ hoàn thành (0 đến 1)
        position.y = baseY - popUpHeight * t; // Di chuyển lên
    } else if (popUpTimer < POP_UP_DURATION + STAY_UP_DURATION) {
        // Giai đoạn ở trên
        position.y = baseY - popUpHeight; // Ở vị trí cao nhất
    } else {
        // Giai đoạn rút xuống
        isPoppingUp = false;
        float t = (popUpTimer - POP_UP_DURATION - STAY_UP_DURATION) / POP_UP_DURATION; // Tỷ lệ hoàn thành (0 đến 1)
        position.y = baseY - popUpHeight * (1.0f - t); // Di chuyển xuống
    }
    Enemy::updateCollision();
    UpdateTexture();
}

void PiranhaPlant::draw() {
    if (isDead() || isReadyForRemoval()) {
        return;
    }
    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
    //Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
    DrawTexturePro(texture, source, dest, {0.f, 0.f}, 0.0f, WHITE);
    
    if (SETTING.getDebugMode()) {
        CollNorth.draw();
        CollSouth.draw();
        CollEast.draw();
        CollWest.draw();
    }   
}

void PiranhaPlant::UpdateTexture() {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("PiranhaPlant_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (currFrame == 0) {
        texture = RESOURCE_MANAGER.getTexture("PiranhaPlant_OPEN");
    }
    else {
        texture = RESOURCE_MANAGER.getTexture("PiranhaPlant_CLOSED");
    }
}

ENEMY_TYPE PiranhaPlant::getEnemyType() const
{
    return PIRANHA;
}

void PiranhaPlant::stomped()
{
    if (isDead() || state == STATE_IS_DYING || invincibilityTimer > 0.f)
        return;
    state = STATE_IS_DYING;
    velocity = { 0.f, 0.f };
    deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
    invincibilityTimer = 0.5f;
    updateSquashEffect();
    UpdateTexture();
    Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_REX).c_str()), getCenter());
    globalGameEngine->addEffect(score);
}

float PiranhaPlant::getScores() const
{
    return SCORE_STOMP_REX;
}

float popUpTimer; // Timer để kiểm soát chu kỳ trồi/rút
bool isPoppingUp; // Trạng thái trồi lên hay rút xuống
float popUpHeight; // Độ cao tối đa khi trồi lên
float baseY; // Vị trí Y ban đầu (đáy ống)
float invincibilityTimer;
float delayTimer;
void PiranhaPlant::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
    piranhaType = static_cast<PIRANHA_TYPE>(j["piranhaType"].get<int>());
    popUpTimer = j["popUpTimer"];
    isPoppingUp = j["isPoppingUp"];
    popUpHeight = j["popUpHeight"];
    baseY = j["baseY"];
    invincibilityTimer = j["invincibilityTimer"];
    delayTimer = j["delayTimer"];
}

void PiranhaPlant::saveEntity(json& j) const
{
    Enemy::saveEntity(j);
    j["piranhaType"] = static_cast<int>(piranhaType);
    j["popUpTimer"] = popUpTimer;
    j["isPoppingUp"] = isPoppingUp;
    j["popUpHeight"] = popUpHeight;
    j["baseY"] = baseY;
    j["invincibilityTimer"] = invincibilityTimer;
    j["delayTimer"] = delayTimer;
}
