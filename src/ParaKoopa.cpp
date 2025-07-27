// ParaKoopa.cpp
#include "../include/ParaKoopa.h"
#include "../include/ResourceManager.h"

static constexpr float RED_JUMP_INTERVAL = 2.5f;
static constexpr float RED_JUMP_VELOCITY = 250.0f;
static constexpr float RED_RUN_SPEED = 80.0f;

static constexpr float BLUE_JUMP_INTERVAL = 1.2f;
static constexpr float BLUE_JUMP_VELOCITY = 180.0f;
static constexpr float BLUE_RUN_SPEED = 40.0f;

ParaKoopa::ParaKoopa(Vector2 pos, Texture2D texture)
    : Koopa(pos, texture), jumpTimer(0.0f) {
}

ParaKoopaRed::ParaKoopaRed(Vector2 pos, Texture2D texture) : ParaKoopa(pos, texture) {

}

void ParaKoopaRed::Update() {
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > RED_JUMP_INTERVAL) {
        velocity.y = -RED_JUMP_VELOCITY;
        state = JUMPING;
        jumpTimer = 0.0f;
    }

    Koopa::Update();
}

void ParaKoopaRed::UpdateTexture() {
    if (state == STATE_SHELL || state == STATE_IS_DYING) {
        if (state == STATE_SHELL && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = Singleton<ResourceManager>::getInstance()
                .getTexture("ParaKoopaRed_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = Singleton<ResourceManager>::getInstance()
                .getTexture("ParaKoopaRed_Shell_3");
        }
        return;
    }
 
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }
    if (direction == LEFT) {
        texture = Singleton<ResourceManager>::getInstance()
            .getTexture("ParaKoopaRed_LEFT_" + std::to_string(currFrame));
    }
    else {
        texture = Singleton<ResourceManager>::getInstance()
            .getTexture("ParaKoopaRed_RIGHT_" + std::to_string(currFrame));
    }
}

ParaKoopaBlue::ParaKoopaBlue(Vector2 pos, Texture2D texture)
    : ParaKoopa(pos, texture) {
}

void ParaKoopaBlue::Update() {
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > BLUE_JUMP_INTERVAL) {
        velocity.y = -BLUE_JUMP_VELOCITY;
        state = JUMPING;
        jumpTimer = 0.0f;
    }

    Koopa::Update();


}

void ParaKoopaBlue::UpdateTexture() {
    if (state == STATE_SHELL || state == STATE_IS_DYING) {
        if (state == STATE_SHELL && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = Singleton<ResourceManager>::getInstance()
                .getTexture("BlueKoopa_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = Singleton<ResourceManager>::getInstance()
                .getTexture("BlueKoopa_Shell_3");
        }
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }
    if (direction == LEFT) {
        texture = Singleton<ResourceManager>::getInstance()
            .getTexture("ParaKoopaBlue_LEFT_" + std::to_string(currFrame));
    }
    else {
        texture = Singleton<ResourceManager>::getInstance()
            .getTexture("ParaKoopaBlue_RIGHT_" + std::to_string(currFrame));
    }
}