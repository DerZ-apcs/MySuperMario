#include "../include/PiranhaPlant.h"

// PiranhaPlant Class Implementation
const float PiranhaPlant::POP_UP_DURATION = 1.0f; // Thời gian trồi lên/rút xuống
const float PiranhaPlant::STAY_UP_DURATION = 2.0f; // Thời gian ở trạng thái trồi lên

PiranhaPlant::PiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario)
    : Enemy(pos, { 32, 66 }, { 0, 0 }, RIGHT, ON_GROUND, texture, 0.2f, 1, RED),
    popUpTimer(0.0f), isPoppingUp(true), popUpHeight(48.0f), baseY(pos.y), mario(mario), delayTimer(0.2f), invincibilityTimer(0.0f) { 
}

void PiranhaPlant::Update() {
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
            position.y = baseY; // Giữ ẩn trong ống trong độ trễ
            UpdateTexture();
            UpdatePhysics();
            return;
        }
    }

    popUpTimer += deltaTime;

    float cycleTime = 2 * POP_UP_DURATION + STAY_UP_DURATION;

    if (popUpTimer >= cycleTime) {
        popUpTimer = 0.0f; // Reset chu kỳ
    }

    if (popUpTimer < POP_UP_DURATION) {
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

    UpdatePhysics();
    UpdateTexture();
}

void PiranhaPlant::draw() {
    if (!isDead) {
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x + 30, position.y, texture.width * squashScale, texture.height * squashScale };
        Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
#ifdef DEBUG
        CollNorth.draw();
        CollSouth.draw();
        CollEast.draw();
        CollWest.draw();
#endif
    }
}

void PiranhaPlant::UpdateTexture() {
    if (isDead || state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (currFrame == 0) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_OPEN");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_CLOSED");
    }
}

void PiranhaPlant::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING || mario.getInvincibilityTimer() > 0 || invincibilityTimer > 0) return;

    // Chỉ gây sát thương khi ở trạng thái trồi lên hoàn toàn
    bool isFullyPoppedUp = (popUpTimer >= POP_UP_DURATION && popUpTimer < POP_UP_DURATION + STAY_UP_DURATION);


    // Mario nhảy lên đầu (stomp)
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        invincibilityTimer = 0.5f;
        mario.setVelY(MARIO_BOUNCE_VELOCITY);
        mario.addScore(SCORE_STOMP_GOOMBA);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
    }
    else if ((collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) && isFullyPoppedUp) {
        if (mario.getMarioState() == STATE_SUPER || mario.getMarioState() == STATE_FIRE_BALL) {
            mario.TransitionToSmall();
            mario.setInvincibilityTimer(2.0f);
        }
        else {
            mario.setState(STATE_IS_DYING);
            Singleton<ResourceManager>::getInstance().playSound("MARIO_DIE");
        }
    }
}

void PiranhaPlant::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    // Piranha Plant không va chạm với các enemy khác
}

void PiranhaPlant::HandleTileCollision(const Tile& tile, CollisionType collType) {
    // Piranha Plant không xử lý va chạm với tile vì nó cố định trong ống
}
