#include "../include/Rex.h"
#include "../include/GameEngine.h"

// Rex Class Implementation
Rex::Rex(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 40, 64 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BLUE),
    rexState(REX_NORMAL), detectMarioRange(250.0f) {
    velocity.x = -REX_SPEED; // REX_SPEED được định nghĩa trong Enemy.h
    updateCollision();
    collisionTimer = 0.f;
    enemyType = REX;
}

ENEMY_TYPE Rex::getEnemyType() const
{
    return REX;
}

float Rex::getScores() const
{
    return SCORE_STOMP_REX;
}

void Rex::Update() {
    Entity::Update();
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    const float deltaTime = GetFrameTime();

    if (collisionTimer > 0) {
        collisionTimer -= deltaTime;
    }

    //Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p && p->getState() != STATE_IS_DYING && collisionTimer <= 0) {
            float distance = Vector2Distance(position, p->getPosition());
            if (distance <= detectMarioRange) {
                // Mario trong phạm vi phát hiện, thay đổi hướng và tốc độ
                if (p->getX() < position.x) {
                    direction = LEFT;
                    velocity.x = (rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED;
                }
                else {
                    direction = RIGHT;
                    velocity.x = (rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED;
                }
            }
            else {
                // Mario ngoài phạm vi, di chuyển bình thường
                velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
                    ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
            }
        }
        else {
            // Di chuyển bình thường
            velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
                ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
        }
    }
   
    if (velocity.y > 50)
        state = FALLING;
    if (getGravityAvailable()) {
        velocity.y += GRAVITY * deltaTime;
    }
    position.y += velocity.y * deltaTime;
    position.x += velocity.x * deltaTime;
    updateCollision();
    UpdateTexture();
}

void Rex::draw() {
    Enemy::draw();
}

void Rex::UpdateTexture() {
    std::string dir = direction == RIGHT ? "_RIGHT_" : "_LEFT_";
    std::string Rstate = rexState == REX_NORMAL ? "Rex" : "Rex_Compressed";

    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Rex_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }
    if (state == ON_GROUND) {
        texture = RESOURCE_MANAGER.getTexture(Rstate + dir + to_string(currFrame));
    }
    else if (state == FALLING || state == JUMPING) {
        texture = RESOURCE_MANAGER.getTexture(Rstate + dir + "0");
    }
}

void Rex::stomped()
{
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;

    if (rexState == REX_NORMAL) {
        // Lần giẫm đầu: Chuyển sang trạng thái nén
        rexState = REX_COMPRESSED;
        setSize({ 32, 32 });
        setY(getY() + 32); // Điều chỉnh vị trí cho kích thước nhỏ hơn
        velocity.x = (direction == LEFT) ? -REX_COMPRESSED_SPEED : REX_COMPRESSED_SPEED;
        updateCollision();
    }
    else {
        // Lần giẫm thứ hai: Chuyển sang trạng thái chết
        state = STATE_IS_DYING;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        updateSquashEffect();
        Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_REX).c_str()), getCenter());
        globalGameEngine->addEffect(score);
    }
}

void Rex::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
    rexState = static_cast<RexState>(j["rexState"].get<int>());
    detectMarioRange = j["detectMarioRange"];
}

void Rex::saveEntity(json& j) const
{
    Enemy::saveEntity(j);
    j["rexState"] = static_cast<int>(rexState);
    j["detectMarioRange"] = detectMarioRange;
}


void Rex::updateCollision() {
    // Cập nhật kích thước hộp va chạm dựa trên trạng thái của Rex
    if (rexState == REX_NORMAL) {
        this->size = { 40, 64 };
        CollNorth.setSize({ size.x - 15, 5 });
        CollSouth.setSize({ size.x - 15, 5 });
        CollEast.setSize({ 5, size.y * 0.8f });
        CollWest.setSize({ 5, size.y * 0.8f });
    }
    else if (rexState == REX_COMPRESSED) {
        this->size = { 32, 32 };
        CollNorth.setSize({ size.x - 15, 5 });
        CollSouth.setSize({ size.x - 15, 5 });
        CollEast.setSize({ 5, size.y * 0.8f });
        CollWest.setSize({ 5, size.y * 0.8f });
    }

    // Cập nhật vị trí hộp va chạm (không sử dụng squashScale khi không ở trạng thái chết)
    if (state != STATE_IS_DYING) {
        squashScale = 1.0f; // Đảm bảo không áp dụng squashScale khi không chết
    }
    Entity::updateCollision();
}