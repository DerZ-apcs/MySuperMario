// JumpingPiranhaPlant.cpp
#include "../include/JumpingPiranhaPlant.h"
#include "../include/Mario.h"
#include "../include/ResourceManager.h"
#include <raylib.h>

const float JumpingPiranhaPlant::ANIM_INTERVAL = 1.0f;   
const float JumpingPiranhaPlant::JUMP_HEIGHT = 40.0f;  

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

    position.y = baseY - offsetRatio * JUMP_HEIGHT;

    UpdatePhysics();
    UpdateTexture();
}

void JumpingPiranhaPlant::UpdateTexture() {
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (currFrame == 0) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMPING_1");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMPING_2");
    }
}

void JumpingPiranhaPlant::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING || mario.getInvincibilityTimer() > 0 || invincibilityTimer > 0) return;

    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        invincibilityTimer = 0.5f;
        mario.setVelY(-MARIO_BOUNCE_VELOCITY);
        mario.addScore(SCORE_STOMP_GOOMBA);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
        return;
    }
    if ((collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH)) {
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