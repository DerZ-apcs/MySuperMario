#include "../include/Goomba.h"
#include "../include/GameEngine.h"

// Goomba Class Implementation
Goomba::Goomba(Vector2 pos, Texture2D texture)
    : Enemy(pos, { (float)texture.width, (float)texture.height }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BROWN), detectMarioRange(300.0f),
	goombaType(NORMAL_GOOMBA), collisionTimer(0.f)
{ 
    velocity.x = -GOOMBA_SPEED;
    collisionTimer = 0.f;
    scores = SCORE_STOMP_GOOMBA;
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
    bool marioDetected = false;
    bool sameHeight = false;
    bool sameVertical = false;
    Vector2 marioPos;

    // 1. Logic phát hiện Mario
    if (collisionTimer <= 0) {
        for (auto& p : globalGameEngine->getMultiplayers()) {
            if (p != nullptr && p->getPhase() != DEAD_PHASE && p->getPhase() != CLEARLEVEL_PHASE) {
				float dist = Vector2Distance(position, p->getPosition());
                if (dist <= detectMarioRange) {
                    marioDetected = true;
                    // ktra chenh lech do cao
                    float heightDiff = fabs(p->getBottom() - getBottom());
					if (heightDiff < 16.0f) { // nếu chênh lệch chiều cao nhỏ hơn 16 pixel
						sameHeight = true;
					}
					if (fabs(p->getPosition().x - position.x) <= 60.0f) { // nếu Mario đang ở trên đầu goomba 
						sameVertical = true;
					}
					marioPos = p->getPosition();
					break; // chỉ cần phát hiện một Mario
                }
            }
        }
    }

    float current_speed = GOOMBA_SPEED;
    if (marioDetected && sameHeight) {
        current_speed *= 1.5f;
		direction = (marioPos.x < position.x) ? LEFT : RIGHT; // Đổi hướng theo Mario
	}
    else if (sameVertical) {
        // Nếu Mario đang ở trên đầu Goomba, Goomba sẽ không đổi hướng
        if (marioDetected) current_speed *= 1.5f;
        direction = (velocity.x < 0) ? LEFT : RIGHT;
    }
	else if (marioDetected) {
		// Nếu Mario không cùng chiều cao, Goomba sẽ không đổi hướng
		direction = (velocity.x < 0) ? LEFT : RIGHT;
	}

    velocity.x = (direction == LEFT) ? -current_speed : current_speed;

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
    collisionTimer = j["collisionTimer"]; // overrides Enemy’s if needed
    detectMarioRange = j["detectMarioRange"];
    goombaType = static_cast<GOOMBA_TYPE>(j["goombaType"].get<int>());
}

void Goomba::saveEntity(json& j) const
{
    Enemy::saveEntity(j); // Save base Enemy and Entity attributes
    j["collisionTimer"] = collisionTimer; // saves Goomba's value
    j["detectMarioRange"] = detectMarioRange;
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

void FlyingGoomba::CollisionWithFireball(FireBall* fireball)
{
    // like stomped
	fireball->setEntityDead();
    if (SETTING.isSoundEnabled())
		RESOURCE_MANAGER.playSound("stomp.wav");
    if (hasWings) {
        SmokeEffect* smokeright = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ 60, 120 });
        globalGameEngine->addEffect(smokeright);
        SmokeEffect* smokeleft = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ -60, 120 });
        globalGameEngine->addEffect(smokeleft);
    }
    stomped();
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

