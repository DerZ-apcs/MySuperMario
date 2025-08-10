#include "../include/BuzzyBeetle.h"
#include "../include/GameEngine.h"

const float BuzzyBeetle::BUZZY_SHELL_SPEED = 200.0f; // Speed when in shell state
const float BuzzyBeetle::BUZZY_WALK_SPEED = 100.0f; // Speed when walking normally
const float BuzzyBeetle::BUZZY_JUMP_SPEED = 200.0f; // Speed when jumping

BuzzyBeetle::BuzzyBeetle(Vector2 pos, Texture2D texture):
	Koopa(pos, texture), BuzzyState(NORMAL_BUZZY)
{
	size = { 32, 32 }; // Default size for BuzzyBeetle
	texture = RESOURCE_MANAGER.getTexture("BuzzyBeetle_LEFT_0");
    reviveShakeTimer = 0.0f;
    isReviving = false;
    reviveTimer = 0.0f;
    scores = SCORE_STOMP_BUZZY;
}

void BuzzyBeetle::UpdateTexture() {
    std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
    if (BuzzyState == SHELL_BUZZY || state == STATE_IS_DYING) {
        if (BuzzyState == SHELL_BUZZY && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 3;
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture("BuzzyBeetle_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = RESOURCE_MANAGER.getTexture("BuzzyBeetle_Shell_0");
        }
    }
    else {
        // for normal_buzzy
        if (state == ON_GROUND) {
            frameAcum += GetFrameTime();
            if (frameAcum > frameTime) {
                currFrame = (currFrame + 1) % (maxFrame + 1);
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture("BuzzyBeetle" + dir + std::to_string(currFrame));
        }
        else if (state == FALLING || state == JUMPING) {
            texture = RESOURCE_MANAGER.getTexture("BuzzyBeetle" + dir + "0");
        }
    }
}




void BuzzyBeetle::Update()
{
    // Xử lý trạng thái chết
    const float deltaTime = GetFrameTime();
    Entity::Update();
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }
    if (BuzzyState == SHELL_BUZZY && velocity.x == 0) {
        reviveTimer += deltaTime; // Bắt đầu đếm giờ
        if (reviveTimer > KOOPA_REVIVE_WARNING_TIME) {
            isReviving = true;
            reviveShakeTimer += deltaTime; // Timer cho hiệu ứng nhấp nháy
        }
        // Khi hết giờ, hồi sinh hoàn toàn
        if (reviveTimer > KOOPA_REVIVE_TIME) {
            state = ON_GROUND;
            BuzzyState = NORMAL_BUZZY;
            setSize({ 32, 32 });
            setY(getY() - 4); // Nâng Koopa lên để vừa với size mới
            isReviving = false; // Tắt trạng thái cảnh báo
            reviveTimer = 0.0f;
            reviveShakeTimer = 0.0f;
            updateCollision();
        }
    }
    else {
        reviveTimer = 0.0f;
        isReviving = false;
        reviveShakeTimer = 0.0f;
    }

    if (state == ON_GROUND && BuzzyState == NORMAL_BUZZY) {
        if (direction == LEFT) {
            velocity.x = -BUZZY_WALK_SPEED;
        }
        else {
            velocity.x = BUZZY_WALK_SPEED;
        }
    }
    if (velocity.y > 20)
        state = FALLING;
    if (getGravityAvailable()) {
        velocity.y += GRAVITY * deltaTime;
    }
    position.y += velocity.y * deltaTime;
    position.x += velocity.x * deltaTime;
    updateCollision();
    UpdateTexture();
}

void BuzzyBeetle::stomped()
{
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    // First stomp: Koopa becomes a stationary shell
    if (BuzzyState != SHELL_BUZZY) {
        BuzzyState = SHELL_BUZZY;
        velocity.x = 0;
        velocity.y = 0;
        setSize({ 32, 28 });
        setY(getY() + 4); // Adjust position for smaller shell size
        updateCollision();
        reviveTimer = 0.0f;
        isReviving = false;
    }
    // Second stomp: Shell disappears
    else {
        state = STATE_IS_DYING;
        velocity.y = -300; // Slight upward bounce
        velocity.x = (rand() % 100) - 50; // Random horizontal velocity
        deathTimer = ENEMY_DEATH_TIMER_LONG; // Disappear after 0.5s
        Effect* text = new ScoreEffect(RESOURCE_MANAGER.getTexture(to_string(SCORE_STOMP_BUZZY).c_str()), getCenter());
        globalGameEngine->addEffect(text);
    }
}

void BuzzyBeetle::kicked(Direction direction)
{
    if (BuzzyState != SHELL_BUZZY || velocity.x != 0)
        return;
    // kick the shell
    this->isKicked = true;
    velocity.x = (direction == LEFT) ? BUZZY_SHELL_SPEED : -BUZZY_SHELL_SPEED;
    this->direction = (direction == LEFT) ? RIGHT : LEFT;
    reviveTimer = 0.0f;
    isReviving = false;
}

ENEMY_TYPE BuzzyBeetle::getEnemyType() const
{
	return BuzzyState == SHELL_BUZZY ? SHELL : BUZZYBEETLE;
}

void BuzzyBeetle::loadEntity(const json& j)
{
    Koopa::loadEntity(j);
    BuzzyState = static_cast<BuzzyBeetleState>(j["BuzzyState"].get<int>());
}

void BuzzyBeetle::saveEntity(json& j) const
{
    Koopa::saveEntity(j);
    j["BuzzyState"] = static_cast<int>(BuzzyState);
}
