#include "../include/BoomBoom.h"
#include "../include/GameEngine.h" // Để lấy FrameTime và thêm hiệu ứng
#include "../include/ResourceManager.h" // Để quản lý texture (giả định)
#include "../include/Shockwave.h"

const float BOOMBOOM_WALK_SPEED = 100.0f;
const float BOOMBOOM_CHARGE_SPEED = 450.0f;
const float BOOMBOOM_JUMP_POWER = -900.0f;
const float BOOMBOOM_ACTION_INTERVAL = 3.0f; // Thời gian giữa các hành động
const float BOOMBOOM_SPIN_DURATION = 1.0f;   // Thời gian quay trước khi lao
const float BOOMBOOM_STUN_DURATION = 1.5f;   // Thời gian bị choáng
const float BOOMBOOM_CHARGE_DURATION = 1.5f;
const float JUMP_APEX_DURATION = 0.4f;      // Cải tiến: Thời gian dừng trên không (0.4 giây)
const float GROUND_POUND_SPEED = 400.0f;   // Cải tiến: Tốc độ lao xuống
const float GROUND_POUND_RADIUS_X = 80.0f;  
const float GROUND_POUND_RADIUS_Y = 32.0f;  
const int   BOOMBOOM_INITIAL_HP = 3;         // Máu khởi điểm

BoomBoom::BoomBoom(Vector2 pos, Character* player)
    : Boss(pos, { 64, 64 }, RESOURCE_MANAGER.getTexture("boomboom_walk"), BOOMBOOM_INITIAL_HP),
    target(player),
    walkSpeed(BOOMBOOM_WALK_SPEED),
    chargeSpeed(BOOMBOOM_CHARGE_SPEED),
    jumpPower(BOOMBOOM_JUMP_POWER),
    actionTimer(BOOMBOOM_ACTION_INTERVAL)
{
    currentFrame = 0;
    frameTimer = 0.0f;
    frameDuration = 0.15f; 
    isEnraged = false;
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
    case BoomBoomState::WALKING: {
        vulnerable = true;
        float currentWalkSpeed = isEnraged ? walkSpeed * 1.5f : walkSpeed;
        velocity.x = currentWalkSpeed * (direction == RIGHT ? 1 : -1);
        velocity.y = 0;
        actionTimer = isEnraged ? BOOMBOOM_ACTION_INTERVAL * 0.7f : BOOMBOOM_ACTION_INTERVAL;
        currentFrame = 0;
        frameTimer = 0.0f;
        if (direction == LEFT) {
            setTexture(walkLeftTextures[currentFrame]);
        }
        else {
            setTexture(walkRightTextures[currentFrame]);
        }
        break;
    }
    case BoomBoomState::JUMP_ASCEND:
        vulnerable = false;
        velocity.y = jumpPower; 
        setGravityAvailable(true);
        setState(JUMPING);
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_jump")); 
        break;

    case BoomBoomState::JUMP_APEX:
        vulnerable = false;
        velocity = { 0, 0 }; 
        setGravityAvailable(false); 
        statePhaseTimer = JUMP_APEX_DURATION; 
        // Có thể đổi texture khác nếu muốn
        break;

    case BoomBoomState::JUMP_DESCEND:
        vulnerable = false;
        velocity.y = GROUND_POUND_SPEED; 
        setGravityAvailable(true); 
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_fall")); 
        break;

    case BoomBoomState::SPINNING:
        vulnerable = false; // Bất tử khi đang quay
        velocity.x = 0;
        statePhaseTimer = isEnraged ? BOOMBOOM_SPIN_DURATION * 0.7f : BOOMBOOM_SPIN_DURATION;
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_spin"));
        break;

    case BoomBoomState::CHARGING: {
        vulnerable = false;
        float currentChargeSpeed = isEnraged ? chargeSpeed * 1.3f : chargeSpeed;
        if (direction == LEFT) {
            velocity.x = -currentChargeSpeed;
        }
        else {
            velocity.x = currentChargeSpeed;
        }
        statePhaseTimer = BOOMBOOM_CHARGE_DURATION;
        setTexture(RESOURCE_MANAGER.getTexture("boomboom_charge"));
        break;
    }
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
    case BoomBoomState::JUMP_ASCEND:  updateJumpAscend();   break;
    case BoomBoomState::JUMP_APEX:    updateJumpApex();     break; 
    case BoomBoomState::JUMP_DESCEND: updateJumpDescend();  break;
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
            enterState(BoomBoomState::JUMP_ASCEND);
        }
        else {
            enterState(BoomBoomState::SPINNING);
        }
    }
}

void BoomBoom::updateJumpAscend() {
    if (velocity.y >= 0) {
        enterState(BoomBoomState::JUMP_APEX);
    }
}

void BoomBoom::updateJumpApex() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(BoomBoomState::JUMP_DESCEND);
    }
}

void BoomBoom::updateJumpDescend() {
    // Khi chạm đất
    if (state == ON_GROUND) {
        //Rectangle damageArea = {
        //    getCenter().x - GROUND_POUND_RADIUS_X, // Vị trí x bắt đầu
        //    getBottom() - GROUND_POUND_RADIUS_Y,   // Vị trí y bắt đầu (từ mặt đất lên)
        //    GROUND_POUND_RADIUS_X * 2,             // Chiều rộng của vùng sát thương
        //    GROUND_POUND_RADIUS_Y                  // Chiều cao của vùng sát thương
        //};
        //if (CheckCollisionRecs(damageArea, target->getRect())) {
        //   // target->takeDamage(1);
        //}
        actionTimer -= GetFrameTime();
        if (actionTimer <= 0) {
            int choice = GetRandomValue(0, 1);
            if (choice == 0) {
                enterState(BoomBoomState::WALKING);
            }
            else {
                enterState(BoomBoomState::SPINNING);
            }
        }
        //enterState(BoomBoomState::WALKING);
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
        if (currentHp == 1 && !isEnraged) {
            isEnraged = true;
        }
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
    if (currentState == BoomBoomState::WALKING || currentState == BoomBoomState::STUNNED) {
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