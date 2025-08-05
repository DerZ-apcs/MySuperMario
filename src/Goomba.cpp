#include "../include/Goomba.h"
#include "../include/GameEngine.h"

// Goomba Class Implementation
Goomba::Goomba(Vector2 pos, Texture2D texture)
    : Enemy(pos, { (float)texture.width, (float)texture.height }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BROWN),
    pauseTimer(0.0f), isPaused(false), detectMarioRange(200.0f), beattacked(false) {
    velocity.x = -GOOMBA_SPEED;
    collisionTimer = 0.f;
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

    if (collisionTimer > 0) {
        collisionTimer -= deltaTime;
    }

    //Character* character = globalGameEngine->getMultiplayers() ? globalGameEngine->getCharacter() : nullptr;
    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p != nullptr && p->getPhase() != DEAD_PHASE && p->getPhase() != CLEARLEVEL_PHASE && collisionTimer <= 0) {
            float distance = Vector2Distance(position, p->getPosition());
            if (distance <= detectMarioRange) {
                // Mario trong phạm vi phát hiện, thay đổi hành vi
                if (p->getX() < position.x) {
                    direction = LEFT;
                    velocity.x = -GOOMBA_SPEED * 1.5f; // Tăng tốc độ khi đuổi
                }
                else {
                    direction = RIGHT;
                    velocity.x = GOOMBA_SPEED * 1.5f; // Tăng tốc độ khi đuổi
                }
            }
            else {
                // Mario ngoài phạm vi, di chuyển bình thường
                if (state == ON_GROUND) {
                    velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
                }
            }
        }
        else {
            if (isPaused) {
                pauseTimer -= deltaTime;
                if (pauseTimer <= 0) {
                    isPaused = false;
                    direction = (direction == LEFT) ? RIGHT : LEFT;
                    velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
                }
                velocity.x = 0;
            }
            else {
                if (state == ON_GROUND) {
                    if (collisionTimer <= 0) {
                        velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
                    }
                    if (GetRandomValue(0, 1000) < 3) { // 0.3% cơ hội dừng lại
                        isPaused = true;
                        pauseTimer = GetRandomValue(5, 15) / 10.0f; // Dừng 0.5-1.5 giây
                    }
                }
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
        /*isFlipped = true;*/
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
    Effect* text = new TextEffect(to_string(SCORE_STOMP_GOOMBA).c_str(), getCenter());
    globalGameEngine->addEffect(text);
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

