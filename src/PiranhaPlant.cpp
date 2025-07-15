#include "../include/PiranhaPlant.h"
#include "../include/GameEngine.h"

// PiranhaPlant Class Implementation
const float PiranhaPlant::POP_UP_DURATION = 1.0f; // Thời gian trồi lên/rút xuống
const float PiranhaPlant::STAY_UP_DURATION = 2.0f; // Thời gian ở trạng thái trồi lên

PiranhaPlant::PiranhaPlant(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 32 }, { 0, 0 }, RIGHT, ON_GROUND, texture, 0.2f, 1, RED),
    popUpTimer(0.0f), isPoppingUp(true), popUpHeight(66.0f), baseY(pos.y), delayTimer(0.2f), invincibilityTimer(0.0f) { 
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
    Entity::updateCollision();
    UpdateTexture();
}

void PiranhaPlant::draw() {
    if (isDead() || isReadyForRemoval()) {
        return;
    }

    float emergedHeight = baseY - position.y;
    if (emergedHeight <= 0) {
        return;
    }

    if (emergedHeight > popUpHeight) {
        emergedHeight = popUpHeight;
    }

    // Vẽ chỉ phần texture tương ứng với độ cao trồi lên
    Rectangle source = { 0.0f, (float)texture.height - emergedHeight - 10, (float)texture.width, emergedHeight };
    Rectangle dest = { position.x, position.y, (float)texture.width * squashScale, emergedHeight * squashScale };
    Vector2 origin = { (texture.width * squashScale) / 2, 0 }; // Origin ở giữa trục X, đầu trên trục Y

    DrawTexturePro(texture, source, dest, origin, 0.1f, WHITE);

    // Chỉ vẽ các vùng va chạm khi cây trồi lên đủ cao
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
    Effect* text = new TextEffect(to_string(SCORE_STOMP_REX).c_str(), getCenter());
    globalGameEngine->addEffect(text);
}

float PiranhaPlant::getScores() const
{
    return SCORE_STOMP_REX;
}

//void PiranhaPlant::CollisionWithCharacter(Mario& mario, CollisionType collType) {

//    // Chỉ gây sát thương khi ở trạng thái trồi lên hoàn toàn
//    bool isFullyPoppedUp = (popUpTimer >= POP_UP_DURATION && popUpTimer < POP_UP_DURATION + STAY_UP_DURATION);
//
//
//    // Mario nhảy lên đầu (stomp)
//    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
//        state = STATE_IS_DYING;
//        velocity.x = 0;
//        velocity.y = 0;
//        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
//        invincibilityTimer = 0.5f;
//        mario.setVelY(MARIO_BOUNCE_VELOCITY);
//        mario.addScore(SCORE_STOMP_GOOMBA);
//        RESOURCE_MANAGER.playSound("STOMP");
//        updateSquashEffect();
//        UpdateTexture();
//    }
//    else if ((collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) && isFullyPoppedUp) {
//        if (mario.getMarioState() == STATE_SUPER || mario.getMarioState() == STATE_FIRE_BALL) {
//            mario.TransitionToSmall();
//            mario.setInvincibilityTimer(2.0f);
//        }
//        else {
//            mario.setState(STATE_IS_DYING);
//            RESOURCE_MANAGER.playSound("MARIO_DIE");
//        }
//    }
//}
