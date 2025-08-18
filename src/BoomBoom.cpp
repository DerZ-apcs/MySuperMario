#include "../include/BoomBoom.h"
#include "../include/GameEngine.h" // Để lấy FrameTime và thêm hiệu ứng
#include "../include/ResourceManager.h" // Để quản lý texture (giả định)

const float BOOMBOOM_WALK_SPEED = 100.0f;
const float BOOMBOOM_CHARGE_SPEED = 450.0f;
const float BOOMBOOM_JUMP_POWER = -500.0f;
const float BOOMBOOM_ACTION_INTERVAL = 3.0f; // Thời gian giữa các hành động
const float BOOMBOOM_SPIN_DURATION = 1.0f;   // Thời gian quay trước khi lao
const float BOOMBOOM_STUN_DURATION = 1.5f;   // Thời gian bị choáng
const float BOOMBOOM_CHARGE_DURATION = 1.5f;
const int   BOOMBOOM_INITIAL_HP = 3;         // Máu khởi điểm

BoomBoom::BoomBoom(Vector2 pos):
    Boss(pos, { 64, 64 }, RESOURCE_MANAGER.getTexture("boomboom_walk_left_0"), BOOMBOOM_INITIAL_HP),
    walkSpeed(BOOMBOOM_WALK_SPEED),
    chargeSpeed(BOOMBOOM_CHARGE_SPEED),
    jumpPower(BOOMBOOM_JUMP_POWER), 
    actionTimer(BOOMBOOM_ACTION_INTERVAL)
{
    currentFrame = 0;
    frameTimer = 0.0f;
    frameDuration = 0.15f;
    gravityAvailable = true;
    collisionAvailable = true;
    loadAnimations();
    enterState(BoomBoomState::WALKING);
}

BoomBoom::BoomBoom(Vector2 pos, Character* player)
    : Boss(pos, { 64, 64 }, RESOURCE_MANAGER.getTexture("boomboom_walk_left_0"), BOOMBOOM_INITIAL_HP),
    /*target(player)*/
    walkSpeed(BOOMBOOM_WALK_SPEED),
    chargeSpeed(BOOMBOOM_CHARGE_SPEED),
    jumpPower(BOOMBOOM_JUMP_POWER),
    actionTimer(BOOMBOOM_ACTION_INTERVAL)
{
    currentFrame = 0;
    frameTimer = 0.0f;
    frameDuration = 0.15f; 

    loadAnimations(); 
    enterState(BoomBoomState::WALKING);
}

void BoomBoom::loadAnimations() {
    walkLeftTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_left_0"));
    walkLeftTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_left_1"));
    walkLeftTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_left_2"));

    walkRightTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_right_0"));
    walkRightTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_right_1"));
    walkRightTextures.push_back(RESOURCE_MANAGER.getTexture("boomboom_walk_right_2"));
}

float BoomBoom::getScores() const { 
    return 1000.0f; 
}

void BoomBoom::enterState(BoomBoomState newState) {
    currentState = newState;
    stateTimer = 0.0f; // Reset state-wide timer

    switch (currentState) {
    case BoomBoomState::WALKING:
        vulnerable = true;
        velocity.x = walkSpeed * (direction == RIGHT ? 1 : -1);
        velocity.y = 0;
        actionTimer = BOOMBOOM_ACTION_INTERVAL; // Reset bộ đếm hành động
        currentFrame = 0;
        frameTimer = 0.0f;
        if (direction == LEFT) {
            setTexture(walkLeftTextures[currentFrame]);
        }
        else {
            setTexture(walkRightTextures[currentFrame]);
        }
        break;

    case BoomBoomState::JUMPING:
        vulnerable = true;
        velocity.y = jumpPower;
        setState(JUMPING); // Set trạng thái của Enemy base class
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_jump"));
        break;

    case BoomBoomState::SPINNING:
        vulnerable = false; // Bất tử khi đang quay
        velocity.x = 0;
        statePhaseTimer = BOOMBOOM_SPIN_DURATION;
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_spin"));
        break;

    case BoomBoomState::CHARGING:
        vulnerable = false;
        if (direction == LEFT) {
            velocity.x = -chargeSpeed;
        }
        else { 
            velocity.x = chargeSpeed;
        }
        statePhaseTimer = BOOMBOOM_CHARGE_DURATION;
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_charge"));
        break;

    case BoomBoomState::STUNNED:
        vulnerable = true; // Có thể bị tấn công khi choáng
        velocity.x = 0;
        statePhaseTimer = BOOMBOOM_STUN_DURATION;
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_stunned"));
        break;

    case BoomBoomState::HIDDEN:
        vulnerable = false; // Bất tử khi ở trong mai
        velocity.x = 0;
        statePhaseTimer = 3.0f; // Thời gian ẩn mình
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_hidden"));
        break;
    }
}

void BoomBoom::updateBehavior() {
    float dt = GetFrameTime();
    stateTimer += dt;

    switch (currentState) {
    case BoomBoomState::WALKING:  updateWalking();  break;
    case BoomBoomState::JUMPING:  updateJumping();  break;
    case BoomBoomState::SPINNING: updateSpinning(); break;
    case BoomBoomState::CHARGING: updateCharging(); break;
    case BoomBoomState::STUNNED:  updateStunned();  break;
    case BoomBoomState::HIDDEN:   updateHidden();   break;
    }
}

void BoomBoom::updateWalking() {
    frameTimer += GetFrameTime();
    if (frameTimer >= frameDuration) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % walkLeftTextures.size();
    }

    if (direction == LEFT) {
        setTexture(walkLeftTextures[currentFrame]);
    }
    else {
        setTexture(walkRightTextures[currentFrame]);
    }
    actionTimer -= GetFrameTime();
    if (actionTimer <= 0) {
        int choice = GetRandomValue(0, 1);
        if (choice == 0) {
            enterState(BoomBoomState::JUMPING);
        }
        else {
            enterState(BoomBoomState::SPINNING);
        }
    }
}

void BoomBoom::updateJumping() {
    if (state == ON_GROUND && velocity.y == 0) {
        enterState(BoomBoomState::WALKING);
    }
}

void BoomBoom::updateSpinning() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(BoomBoomState::CHARGING);
    }
}

void BoomBoom::updateCharging() {
    statePhaseTimer -= GetFrameTime(); 
    if (statePhaseTimer <= 0) {
        enterState(BoomBoomState::STUNNED);
    }
}

void BoomBoom::updateStunned() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(BoomBoomState::WALKING);
    }
}

void BoomBoom::updateHidden() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(BoomBoomState::WALKING);
    }
}


void BoomBoom::onHit() {
    if (currentState != BoomBoomState::HIDDEN) {
        enterState(BoomBoomState::HIDDEN);
    }
}

void BoomBoom::onDeath() {
    setGravityAvailable(false);
    velocity = { (float)GetRandomValue(-100, 100), -600 };
}

void BoomBoom::stomped() {
    if (isDying()) return;

    // Chỉ có thể bị dẫm khi không ở trong mai hoặc không choáng
    if (currentState == BoomBoomState::WALKING || currentState == BoomBoomState::JUMPING || currentState == BoomBoomState::STUNNED) {
        takeDamage(1);
    }
}

void BoomBoom::CollisionWithFireball(FireBall* fireball) {
    if (isDying() || !vulnerable) {
        fireball->setEntityDead();
        return;
    }
    enterState(BoomBoomState::STUNNED);
    fireball->setEntityDead(); 
}

void BoomBoom::loadEntity(const json& j)
{
    Boss::loadEntity(j);
    currentState = static_cast<BoomBoomState>(j["currentState"].get<int>());
    walkSpeed = j["walkSpeed"];
    chargeSpeed = j["chargeSpeed"];
    jumpPower = j["jumpPower"];
    actionTimer = j["actionTimer"];
    statePhaseTimer = j["statePhaseTimer"];
    currentFrame = j["currentFrame"];
    frameTimer = j["frameTimer"];
    frameDuration = j["frameDuration"];
}

void BoomBoom::saveEntity(json& j) const
{
    Boss::saveEntity(j);
    j["currentState"] = static_cast<int>(currentState);
    j["walkSpeed"] = walkSpeed;
    j["chargeSpeed"] = chargeSpeed;
    j["jumpPower"] = jumpPower;
    j["actionTimer"] = actionTimer;
    j["statePhaseTimer"] = statePhaseTimer;
    j["currentFrame"] = currentFrame;
    j["frameTimer"] = frameTimer;
    j["frameDuration"] = frameDuration;
}
