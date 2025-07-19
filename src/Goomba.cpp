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

    Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    if (character && character->getPhase() != DEAD_PHASE && character->getPhase() != CLEARLEVEL_PHASE && collisionTimer <= 0) {
        float distance = Vector2Distance(position, character->getPosition());
        if (distance <= detectMarioRange) {
            // Mario trong phạm vi phát hiện, thay đổi hành vi
            if (character->getX() < position.x) {
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

// FlyingGoomba Class Implementation
FlyingGoomba::FlyingGoomba(Vector2 pos, Texture2D texture)
    : Goomba(pos, texture), jumpTimer(0.0f), detectMarioRange(250.0f), collisionTimer(0.0f) {
    velocity.x = -FLYINGGOOMBA_SPEED;
    state = ON_GROUND;
}

void FlyingGoomba::Update() {
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

    Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    if (character && character->getPhase() != CLEARLEVEL_PHASE && character->getPhase() != DEAD_PHASE && collisionTimer <= 0) {
        float distance = Vector2Distance(position, character->getPosition());
        if (distance <= detectMarioRange) {
            // Mario trong phạm vi phát hiện, thay đổi hướng và tốc độ
            if (character->getX() < position.x) {
                direction = LEFT;
                velocity.x = -FLYINGGOOMBA_SPEED * 1.2f; // Tăng tốc khi đuổi
            }
            else {
                direction = RIGHT;
                velocity.x = FLYINGGOOMBA_SPEED * 1.2f; // Tăng tốc khi đuổi
            }
            // Tăng tần suất nhảy khi gần Mario
            if (distance < detectMarioRange * 0.5f && state == ON_GROUND && jumpTimer > FLYINGGOOMBA_JUMP_INTERVAL * 0.5f) {
                velocity.y = -FLYINGGOOMBA_JUMP_VELOCITY;
                state = JUMPING;
                jumpTimer = 0.0f;
            }
        }
        else {
            // Mario ngoài phạm vi, di chuyển bình thường
            velocity.x = (direction == LEFT) ? -FLYINGGOOMBA_SPEED : FLYINGGOOMBA_SPEED;
        }
    }
    else {
        // Không có Mario hoặc Mario đang chết, di chuyển bình thường
        velocity.x = (direction == LEFT) ? -FLYINGGOOMBA_SPEED : FLYINGGOOMBA_SPEED;
    }

    static float hoverTimer = 0.0f;
    hoverTimer += deltaTime;
    float hoverOffset = sin(hoverTimer * 3.0f) * 50.0f; // Dao động ±10 pixel
    position.y += hoverOffset * deltaTime;

    // Logic nhảy
    jumpTimer += deltaTime;
    if (state == ON_GROUND && jumpTimer > FLYINGGOOMBA_JUMP_INTERVAL) {
        velocity.y = -FLYINGGOOMBA_JUMP_VELOCITY; // Nhảy ngẫu nhiên
        state = JUMPING;
        jumpTimer = 0.0f;
        // baseY = position.y;
    }

    // Cập nhật vị trí
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Áp dụng trọng lực nhẹ
    if (state != ON_GROUND) {
        velocity.y += GRAVITY * deltaTime * 0.5f; // Trọng lực nhẹ hơ
        if (velocity.y > 0 && state == JUMPING) {
            state = FALLING;
        }
    }
    //Entity::updateCollision();
    Enemy::updateCollision();
    UpdateTexture();
}

void FlyingGoomba::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Goomba_Dead");
        /* isFlipped = true;*/
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

