#include "BoomBoom.h"
#include "ResourceManager.h"
#include <raylib.h>

BoomBoom::BoomBoom(Vector2 pos, Texture2D texture)
    : Boss(pos, { (float)texture.width, (float)texture.height }, texture, 3),
    state(BoomBoomState::IDLE)
{
    UpdateTexture();
    velocity.x = -GOOMBA_SPEED;
}

void BoomBoom::changeState(BoomBoomState newState) {
    state = newState;
    switch (state) {
    case BoomBoomState::PREPARE_SMASH:
        stateTimer = PREPARE_TIME; break;
    case BoomBoomState::SMASH:
        velocity.y = SMASH_VELOCITY_Y;
        stateTimer = SMASH_DURATION;
        vulnerable = false;
        break;
    case BoomBoomState::ROLL:
        velocity.x = (direction == LEFT ? -ROLL_SPEED : ROLL_SPEED);
        stateTimer = ROLL_DURATION;
        vulnerable = false;
        break;
    case BoomBoomState::STUN:
        velocity = { 0,0 };
        stateTimer = STUN_DURATION;
        vulnerable = false;
        break;
    default: break;
    }
}

void BoomBoom::performSmash() {
    changeState(BoomBoomState::SMASH);
}

void BoomBoom::performRoll() {
    direction = (direction == LEFT ? RIGHT : LEFT);
    changeState(BoomBoomState::ROLL);
}

void BoomBoom::updateBehavior() {
    float dt = GetFrameTime();
    switch (state) {
    case BoomBoomState::IDLE:
        if (GetRandomValue(0, 1000) < 5) changeState(BoomBoomState::PREPARE_SMASH);
        else if (GetRandomValue(0, 1000) < 5) changeState(BoomBoomState::ROLL);
        break;
    case BoomBoomState::PREPARE_SMASH:
        stateTimer -= dt;
        if (stateTimer <= 0) performSmash();
        break;
    case BoomBoomState::SMASH:
    case BoomBoomState::ROLL:
        stateTimer -= dt;
        if (stateTimer <= 0) changeState(BoomBoomState::STUN);
        break;
    case BoomBoomState::STUN:
        stateTimer -= dt;
        if (stateTimer <= 0 && currentHp > 0) {
            state = BoomBoomState::IDLE;
            vulnerable = true;
            velocity.x = (direction == LEFT ? -GOOMBA_SPEED : GOOMBA_SPEED);
        }
        break;
    default: break;
    }
}

void BoomBoom::onHit() {
    changeState(BoomBoomState::STUN);
}

void BoomBoom::onDeath() {
    state = BoomBoomState::DEAD;
    velocity = { 0,-200 };
}

void BoomBoom::UpdateTexture() {
    std::string name;
    switch (state) {
    case BoomBoomState::IDLE:        name = "BoomBoom_IDLE_0"; break;
    case BoomBoomState::PREPARE_SMASH:name = "BoomBoom_WINDUP"; break;
    case BoomBoomState::SMASH:       name = "BoomBoom_SMASH"; break;
    case BoomBoomState::ROLL:        name = "BoomBoom_ROLL"; break;
    case BoomBoomState::STUN:        name = "BoomBoom_STUN"; break;
    default:                          name = "BoomBoom_IDLE_0"; break;
    }
    texture = RESOURCE_MANAGER.getTexture(name);
}
