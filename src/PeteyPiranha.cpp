#include "../include/PeteyPiranha.h"
#include "../include/GameEngine.h"
#include "../include/ResourceManager.h"
#include "../include/EnemyFireBall.h" 

const float PETEY_WALK_SPEED = 80.0f;
const float PETEY_JUMP_POWER = -1000.0f;
const float PETEY_GROUND_POUND_SPEED = 900.0f;
const float PETEY_ACTION_INTERVAL = 4.0f;   // Thời gian giữa các hành động chính
const float PETEY_HOVER_DURATION = 1.0f;    // Thời gian lơ lửng
const float PETEY_VULNERABLE_DURATION = 2.5f; // Thời gian bị choáng
const float PETEY_HURT_DURATION = 0.8f;     // Thời gian thể hiện bị đau
const int   PETEY_INITIAL_HP = 5;           // Máu khởi điểm
const int   SCORE_DEFEAT_PETEY = 5000;

PeteyPiranha::PeteyPiranha(Vector2 pos, Character* player)
    : Boss(pos, { 64, 64 }, RESOURCE_MANAGER.getTexture("petey_walk_right_0"), PETEY_INITIAL_HP),
    target(player),
    walkSpeed(PETEY_WALK_SPEED),
    jumpPower(PETEY_JUMP_POWER),
    groundPoundSpeed(PETEY_GROUND_POUND_SPEED),
    actionTimer(PETEY_ACTION_INTERVAL)
{
    currentFrame = 0;
    frameTimer = 0.0f;
    frameDuration = 0.2f;
    loadAnimations();
    enterState(PeteyPiranhaState::WALKING);
}

void PeteyPiranha::loadAnimations() {
    walkLeftTextures.push_back(RESOURCE_MANAGER.getTexture("petey_walk_left_0"));
    walkLeftTextures.push_back(RESOURCE_MANAGER.getTexture("petey_walk_left_1"));

    walkRightTextures.push_back(RESOURCE_MANAGER.getTexture("petey_walk_right_0"));
    walkRightTextures.push_back(RESOURCE_MANAGER.getTexture("petey_walk_right_1"));

    hurtTexture = RESOURCE_MANAGER.getTexture("petey_hurt");
    vulnerableTexture = RESOURCE_MANAGER.getTexture("petey_vulnerable");
}

float PeteyPiranha::getScores() const {
    return 0.0f;
}

void PeteyPiranha::enterState(PeteyPiranhaState newState) {
    currentState = newState;
    stateTimer = 0.0f; // Reset bộ đếm giờ của trạng thái

    switch (currentState) {
    case PeteyPiranhaState::WALKING:
        vulnerable = false;
        velocity.x = (direction == RIGHT) ? walkSpeed : -walkSpeed;
        velocity.y = 0;
        actionTimer = PETEY_ACTION_INTERVAL;
        break;

    case PeteyPiranhaState::SHOOTING:
        vulnerable = false;
        velocity = { 0, 0 };
        statePhaseTimer = 1.5f; // Thời gian cho hành động bắn
        setTexture(RESOURCE_MANAGER.getTexture("petey_shoot")); // Giả sử có texture này
        shootFireball();
        break;

    case PeteyPiranhaState::BURROW_DOWN:
        vulnerable = false;
        velocity = { 0, 50 }; // Từ từ lún xuống đất
        setGravityAvailable(false); // Tắt trọng lực để kiểm soát việc lún xuống
        setCollisionAvailable(false); // Không thể va chạm khi đang biến mất
        statePhaseTimer = 1.0f; // Thời gian để hoàn thành việc đào xuống
		setTexture(RESOURCE_MANAGER.getTexture("petey_burrow_down")); 
        break;

    case PeteyPiranhaState::HIDDEN:
        velocity = { 0, 0 };
        statePhaseTimer = 1.5f; // Thời gian di chuyển dưới lòng đất
        if (target) {
            targetPosition = target->getPosition();
        }
        break;

    case PeteyPiranhaState::EMERGE:
        // Di chuyển đến vị trí mục tiêu và bắt đầu trồi lên
        position = { targetPosition.x, targetPosition.y + 100 };
        velocity = { 0, -50 }; // Từ từ trồi lên
        statePhaseTimer = 1.0f; // Thời gian để hoàn thành việc trồi lên
        setCollisionAvailable(true);
		setTexture(RESOURCE_MANAGER.getTexture("petey_emerge")); // Giả sử có texture này
        break;

    case PeteyPiranhaState::VULNERABLE:
        vulnerable = true; // Chỉ có thể bị tấn công ở trạng thái này
        velocity = { 0, 0 };
        statePhaseTimer = PETEY_VULNERABLE_DURATION;
        setTexture(vulnerableTexture);
        break;

    case PeteyPiranhaState::HURT:
        vulnerable = false;
        velocity = { 0, 0 };
        statePhaseTimer = PETEY_HURT_DURATION;
        setTexture(hurtTexture);
        break;
    }
}

void PeteyPiranha::updateBehavior() {
    stateTimer += GetFrameTime();
    switch (currentState) {
    case PeteyPiranhaState::WALKING:        updateWalking(); break;
    case PeteyPiranhaState::SHOOTING:       updateShooting(); break;
    case PeteyPiranhaState::BURROW_DOWN:    updateBurrowDown(); break;
    case PeteyPiranhaState::HIDDEN:         updateHidden(); break;
    case PeteyPiranhaState::EMERGE:         updateEmerge(); break;
    case PeteyPiranhaState::VULNERABLE:     updateVulnerable(); break;
    case PeteyPiranhaState::HURT:           updateHurt(); break;
    }

}

void PeteyPiranha::updateWalking() {
    // Cập nhật animation đi bộ
    frameTimer += GetFrameTime();
    if (frameTimer >= frameDuration) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % walkLeftTextures.size();
    }
    setTexture((direction == LEFT) ? walkLeftTextures[currentFrame] : walkRightTextures[currentFrame]);
    velocity.x = (direction == RIGHT) ? walkSpeed : -walkSpeed;

   actionTimer -= GetFrameTime();
    if (actionTimer <= 0) {
       /* int choice = GetRandomValue(0, 1);*/
       /* enterState(choice == 0 ? PeteyPiranhaState::JUMP_ASCEND : PeteyPiranhaState::SHOOTING);*/
        enterState(PeteyPiranhaState::SHOOTING);
    }
}

void PeteyPiranha::updateShooting() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(PeteyPiranhaState::VULNERABLE);
    }
}

void PeteyPiranha::updateBurrowDown() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(PeteyPiranhaState::HIDDEN);
    }
}

void PeteyPiranha::updateHidden() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(PeteyPiranhaState::EMERGE);
    }
}

void PeteyPiranha::updateEmerge() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        position.y = targetPosition.y + 50; // Đảm bảo đúng vị trí trên mặt đất
        setGravityAvailable(true);
        enterState(PeteyPiranhaState::WALKING);
    }
}

void PeteyPiranha::updateVulnerable() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        enterState(PeteyPiranhaState::WALKING);
    }
}

void PeteyPiranha::updateHurt() {
    statePhaseTimer -= GetFrameTime();
    if (statePhaseTimer <= 0) {
        if (currentHp <= 1) { // Thêm logic "enraged" nếu muốn
            walkSpeed *= 1.5f;
        }
        enterState(PeteyPiranhaState::WALKING);
    }
}

void PeteyPiranha::shootFireball() {
    if (!target || target->getPhase() == CLEARLEVEL_PHASE || target->getPhase() == DEAD_PHASE) {
        return;
    }

    //Direction dir = (target->getX() > position.x) ? RIGHT : LEFT;
    //Vector2 fireBallPos = { position.x, position.y + 10 };
    //const int numFireballs = 3;
    //const float angleSpread = 15.0f; // Góc tỏa ra của các viên đạn
    //const float baseSpeed = 300.0f;

    //for (int i = 0; i < numFireballs; ++i) {
    //    float angle = (i - (numFireballs - 1) / 2.0f) * angleSpread;
    //    float rad = angle * DEG2RAD;

    //    float velX = baseSpeed * cosf(rad) * (dir == RIGHT ? 1.0f : -1.0f);
    //    float velY = -200.0f + baseSpeed * sinf(rad); 

    //    Vector2 fireBallVel = { velX, velY };
    //    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f);
    //    globalGameEngine->addEnemyFireBall(fireball);
    //}
}

void PeteyPiranha::onHit() {
    // Phản ứng khi bị tấn công nhưng chưa chết
    enterState(PeteyPiranhaState::HURT);
}

void PeteyPiranha::onDeath() {
    setGravityAvailable(false);
    velocity = { (float)GetRandomValue(-150, 150), -800 }; // Bay lên và xoay tròn
    setCollisionAvailable(false);
}

void PeteyPiranha::stomped() {
    if (isDying()) return;

    if (currentState == PeteyPiranhaState::VULNERABLE) {
        takeDamage(1);
        globalGameEngine->addScore(1000); // Thưởng điểm khi tấn công đúng lúc
        // Nảy người chơi lên
        if (target) {
            target->setVelY(MARIO_BOUNCE_VELOCITY);
        }
    }
}

void PeteyPiranha::CollisionWithFireball(FireBall* fireball) {
    if (isDying() || !fireball) return;

    if (currentState == PeteyPiranhaState::VULNERABLE) {
        takeDamage(1); // Coi như 1 lần dẫm
        globalGameEngine->addScore(500);
    }

    fireball->setEntityDead(); // Phá hủy quả cầu lửa của Mario
}