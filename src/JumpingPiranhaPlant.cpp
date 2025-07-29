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
    UpdateTexture(true);
}

void JumpingPiranhaPlant::Update() {
    float dt = GetFrameTime();
    animTimer += dt;
    if (animTimer >= ANIM_INTERVAL) animTimer -= ANIM_INTERVAL;

    float phase = animTimer / ANIM_INTERVAL;
    float offsetRatio;
    bool isGoingUp;
    if (phase < 0.5f) {
        offsetRatio = phase / 0.5f;
		isGoingUp = true;
    }
    else {
        offsetRatio = 1.0f - (phase - 0.5f) / 0.5f;
        isGoingUp = false;
    }

    position.y = baseY - offsetRatio * JUMP_HEIGHT;

    UpdateTexture(isGoingUp);
}

void JumpingPiranhaPlant::UpdateTexture(bool isGoingUp) {
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % 2;
        frameAcum = 0.0f;
    }

   /* if (isGoingUp) {
        if (currFrame == 0)
            texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMP_UP_0");
        else
            texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMP_UP_1");
    }
    else {
        if (currFrame == 0)
            texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMP_DOWN_0");
        else
            texture = Singleton<ResourceManager>::getInstance().getTexture("PiranhaPlant_JUMP_DOWN_1");
    }*/
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
    Texture2D newTex = Singleton<ResourceManager>::getInstance().getTexture(key);
    if (newTex.id != 0) {
        texture = newTex;
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

