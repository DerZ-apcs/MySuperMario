#include "../include/Goomba.h"
#include "../include/GameEngine.h"

// Goomba Class Implementation
Goomba::Goomba(Vector2 pos, Texture2D texture)
    : Enemy(pos, { (float)texture.width, (float)texture.height }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BROWN),
    pauseTimer(0.0f), isPaused(false), detectMarioRange(200.0f), beattacked(false),
    isChasing(false), isChaseOnCooldown(false), chaseTimer(0.0f),
    goombaType(NORMAL_GOOMBA)
{ 
    velocity.x = -GOOMBA_SPEED;
    collisionTimer = 0.f;
    scores = SCORE_STOMP_GOOMBA;
}
bool Goomba::isAttacked() const
{
    return beattacked;
}
ENEMY_TYPE Goomba::getEnemyType() const
{
    return GOOMBA;
}
GOOMBA_TYPE Goomba::getGoombaType() const
{
    return NORMAL_GOOMBA;
}
void Goomba::Update() {
    Entity::Update();
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }
    const float deltaTime = GetFrameTime();

    const float MAX_CHASE_TIME = 5.0f;
    const float CHASE_COOLDOWN = 3.0f;
    const float HORIZONTAL_DEAD_ZONE = 2.0f; 

    if (collisionTimer > 0) {
        collisionTimer -= deltaTime;
    }

    // 1. Xử lý trạng thái hồi chiêu (cooldown)
    if (isChaseOnCooldown) {
        chaseTimer += deltaTime;
        if (chaseTimer >= CHASE_COOLDOWN) {
            isChaseOnCooldown = false;
            chaseTimer = 0.0f;
        }
    }

    // 2. Logic phát hiện và quyết định truy đuổi
    bool marioDetected = false;
    if (!isChasing && !isChaseOnCooldown && collisionTimer <= 0) {
        for (auto& p : globalGameEngine->getMultiplayers()) {
            if (p != nullptr && p->getPhase() != DEAD_PHASE && p->getPhase() != CLEARLEVEL_PHASE) {
                if (Vector2Distance(position, p->getPosition()) <= detectMarioRange) {
                    isChasing = true;
                    chaseTimer = 0.0f;
                    marioDetected = true;
                    break;
                }
            }
        }
    }

    // 3. Cập nhật trạng thái và vận tốc
    if (isChasing) {
        chaseTimer += deltaTime;
        bool marioStillInRange = false;

        for (auto& p : globalGameEngine->getMultiplayers()) {
            if (p != nullptr && p->getPhase() != DEAD_PHASE && Vector2Distance(position, p->getPosition()) <= detectMarioRange) {
                marioStillInRange = true;

                // --- SỬA ĐỔI: Logic kiểm tra hướng với "vùng chết" ---
                float horizontalDistance = p->getX() - position.x;

                if (horizontalDistance < -HORIZONTAL_DEAD_ZONE) { // Mario ở rõ ràng bên trái
                    direction = LEFT;
                    velocity.x = -GOOMBA_SPEED * 1.5f;
                }
                else if (horizontalDistance > HORIZONTAL_DEAD_ZONE) { // Mario ở rõ ràng bên phải
                    direction = RIGHT;
                    velocity.x = GOOMBA_SPEED * 1.5f;
                }
                else {
                    // Mario đang ở trong "vùng chết" (ngay trên đầu), dừng di chuyển ngang
                    velocity.x = 0;
                }
                break;
            }
        }

        if (!marioStillInRange || chaseTimer >= MAX_CHASE_TIME) {
            isChasing = false;
            isChaseOnCooldown = true;
            chaseTimer = 0.0f;
        }
    }

    if (!isChasing) {
        if (isPaused) {
            pauseTimer -= deltaTime;
            if (pauseTimer <= 0) {
                isPaused = false;
                direction = (direction == LEFT) ? RIGHT : LEFT;
            }
            velocity.x = 0;
        }
        else {
            velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
            if (GetRandomValue(0, 1000) < 3) {
                isPaused = true;
                pauseTimer = GetRandomValue(5, 15) / 10.0f;
            }
        }
    }

    if (velocity.y > 50)
        state = FALLING;
    if (getGravityAvailable()) {
        velocity.y += GRAVITY * deltaTime;
    }
    position.y += velocity.y * deltaTime;
    position.x += velocity.x * deltaTime;
    Entity::updateCollision();
    UpdateTexture();
}
void Goomba::draw() {
    Enemy::draw();
}

void Goomba::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Goomba_Dead");
        isFlipped = true;
        return;
    }
    if (state == ON_GROUND) {
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (direction == LEFT) {
            texture = RESOURCE_MANAGER.getTexture(
                currFrame == 0 ? "Goomba_LEFT_0" : "Goomba_LEFT_1");
        }
        else {
            texture = RESOURCE_MANAGER.getTexture(
                currFrame == 0 ? "Goomba_RIGHT_0" : "Goomba_RIGHT_1");
        }
    }
    else if (state == FALLING) {
        texture = direction == RIGHT ? RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0") : RESOURCE_MANAGER.getTexture("Goomba_LEFT_0");
    }
}

void Goomba::attacked(Direction direction)
{
    Enemy::attacked();
}

float Goomba::getScores() const
{
    return SCORE_STOMP_GOOMBA;
}

void Goomba::stomped() {
    // stomped
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    state = STATE_IS_DYING;

    velocity.x = 0.0f; // Hiệu ứng đẩy nhẹ
    velocity.y = 0.0f; // Nhảy nhẹ lên
    deathTimer = 0.3f;
    updateSquashEffect();
    UpdateTexture();
    Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_GOOMBA).c_str()), getCenter());
    globalGameEngine->addEffect(score);
}

void Goomba::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
    pauseTimer = j["pauseTimer"];
    isPaused = j["isPaused"];
    beattacked = j["beattacked"];
    collisionTimer = j["collisionTimer"]; // overrides Enemy’s if needed
    detectMarioRange = j["detectMarioRange"];
    isChasing = j["isChasing"];
    isChaseOnCooldown = j["isChaseOnCooldown"];
    chaseTimer = j["chaseTimer"];
    goombaType = static_cast<GOOMBA_TYPE>(j["goombaType"].get<int>());
}

void Goomba::saveEntity(json& j) const
{
    Enemy::saveEntity(j); // Save base Enemy and Entity attributes
    j["pauseTimer"] = pauseTimer;
    j["isPaused"] = isPaused;
    j["beattacked"] = beattacked;
    j["collisionTimer"] = collisionTimer; // saves Goomba's value
    j["detectMarioRange"] = detectMarioRange;
    j["isChasing"] = isChasing;
    j["isChaseOnCooldown"] = isChaseOnCooldown;
    j["chaseTimer"] = chaseTimer;
    j["goombaType"] = static_cast<int>(goombaType);

}

// ---------------------------------------------- FLYINGGOOMBA --------------------------------------------------------- 


ENEMY_TYPE FlyingGoomba::getEnemyType() const
{
    return GOOMBA;
}

GOOMBA_TYPE FlyingGoomba::getGoombaType() const
{
    return FLYING_GOOMBA;
}

// FlyingGoomba Class Implementation
FlyingGoomba::FlyingGoomba(Vector2 pos, Texture2D texture)
    : Goomba(pos, texture) {
    goombaType = FLYING_GOOMBA;
    velocity.x = -FLYINGGOOMBA_SPEED;
    state = JUMPING;
    hasWings = true;

    const float flyRange = 96.0f;
    this->bottomY = pos.y;
    this->topY = pos.y - flyRange;
    this->velocity.y = -FLYINGGOOMBA_SPEED * 0.8f;

    const float patrolRange = 160.0f; // Phạm vi tuần tra (ví dụ: 5 ô)
    this->leftPatrolX = pos.x; // Bắt đầu từ vị trí xuất hiện
    this->rightPatrolX = pos.x + patrolRange;
    scores = SCORE_STOMP_GOOMBA;
}

void FlyingGoomba::Update() {
    if (!hasWings) {
        Goomba::Update(); 
        return;
    }
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
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

    if (collisionTimer > 0) {
        collisionTimer -= deltaTime;
    }

    position.y += velocity.y * deltaTime;
    if (position.y < topY) {
        position.y = topY;
        velocity.y *= -1;
    }
    else if (position.y > bottomY) {
        position.y = bottomY;
        velocity.y *= -1;
    }
    state = (velocity.y < 0) ? JUMPING : FALLING;

    position.x += velocity.x * deltaTime;
    if (position.x < leftPatrolX) {
        position.x = leftPatrolX;
        velocity.x *= -1; // Đảo hướng
        direction = RIGHT;
    }
    else if (position.x > rightPatrolX) {
        position.x = rightPatrolX;
        velocity.x *= -1; // Đảo hướng
        direction = LEFT;
    }

    Enemy::updateCollision();
    UpdateTexture();
}

void FlyingGoomba::UpdateTexture() {
    if (!hasWings) {
        Goomba::UpdateTexture();
        return;
    }

    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Goomba_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (direction == LEFT) {
        texture = RESOURCE_MANAGER.getTexture(
            currFrame == 0 ? "FlyingGoomba_LEFT_0" : "FlyingGoomba_LEFT_1");
    }
    else {
        texture = RESOURCE_MANAGER.getTexture(
            currFrame == 0 ? "FlyingGoomba_RIGHT_0" : "FlyingGoomba_RIGHT_1");
    }
}

float FlyingGoomba::getScores() const
{
    return SCORE_STOMP_GOOMBA + 50;
}

void FlyingGoomba::setJumpTimer(float time) {

}

void FlyingGoomba::stomped()
{
	if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    if (hasWings) {
        hasWings = false;
        position.y += 16;
        size = { 32, 32 };
        velocity.y = 0;
        velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
        state = FALLING;
		setGravityAvailable(true);
    }

    else {
        Goomba::stomped();
    }
}

void FlyingGoomba::loadEntity(const json& j)
{
    Goomba::loadEntity(j);
    topY = j["topY"];
    bottomY = j["bottomY"];
    leftPatrolX = j["leftPatrolX"];
    rightPatrolX = j["rightPatrolX"];
    hasWings = j["hasWings"];
}

void FlyingGoomba::saveEntity(json& j) const
{
    Goomba::saveEntity(j);
    j["hasWings"] = hasWings;
    j["topY"] = topY;
    j["bottomY"] = bottomY;
    j["leftPatrolX"] = leftPatrolX;
    j["rightPatrolX"] = rightPatrolX;
}

