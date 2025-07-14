#include "../include/Koopa.h"
#include "../include/GameEngine.h"

// Koopa Class Implementation
Koopa::Koopa(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 54 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, GREEN),
    reviveTimer(0.0f), isReviving(false), reviveShakeTimer(0.0f),
    koopaState(NORMAL_KOOPA), koopaType(YELLOW_KOOPA)
{
}

void Koopa::setKoopaType(KOOPA_TYPE type)
{
    this->koopaType = type;
}

KOOPA_TYPE Koopa::getKoopaType() const
{
    return koopaType;
}

ENEMY_TYPE Koopa::getEnemyType() const
{
    if (koopaState == SHELL_KOOPA)
        return SHELL;
    return KOOPA;
}

void Koopa::Update() {
    // Xử lý trạng thái chết
    const float deltaTime = GetFrameTime();
    Entity::Update();
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    if (koopaState == SHELL_KOOPA && velocity.x == 0) {
        reviveTimer += deltaTime; // Bắt đầu đếm giờ
        if (reviveTimer > KOOPA_REVIVE_WARNING_TIME) {
            isReviving = true;
            reviveShakeTimer += deltaTime; // Timer cho hiệu ứng nhấp nháy
        }
        // Khi hết giờ, hồi sinh hoàn toàn
        if (reviveTimer > KOOPA_REVIVE_TIME) {
            state = ON_GROUND;
            koopaState = NORMAL_KOOPA;
            setSize({ 32, 54 });
            setY(getY() - 22); // Nâng Koopa lên để vừa với size mới
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

    if (state == ON_GROUND && koopaState == NORMAL_KOOPA) {
        if (direction == LEFT) {
            velocity.x = -KOOPA_SPEED;
        }
        else {
            velocity.x = KOOPA_SPEED;
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

void Koopa::draw() {
    if (!isDead()) {
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
        Vector2 origin = { 0, 0 };

        if (isReviving && (int)(reviveShakeTimer * 10) % 2 == 0) {
            DrawTexturePro(texture, source, dest, origin, 0.0f, Fade(WHITE, 0.5f));
        }
        else {
            DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
        }

        CollNorth.draw();
        CollSouth.draw();
        CollEast.draw();
        CollWest.draw();
    }
}

void Koopa::UpdateTexture() {
    std::string dir = direction == RIGHT ? "_RIGHT_" : "_LEFT_";
    std::string colorType = koopaType == YELLOW_KOOPA ? "Yellow" : "Green";
    if (koopaState == SHELL_KOOPA || state == STATE_IS_DYING) {
        if (koopaState == SHELL_KOOPA && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture(colorType + "Koopa_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = RESOURCE_MANAGER.getTexture(colorType + "Koopa_Shell");
        }
    }
    else {
        // for normal_koopa
        if (state == ON_GROUND) {
            frameAcum += GetFrameTime();
            if (frameAcum > frameTime) {
                currFrame = (currFrame + 1) % (maxFrame + 1);
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture(colorType + "Koopa" + dir + std::to_string(currFrame));
        }
        else if (state == FALLING || state == JUMPING) {
            texture = RESOURCE_MANAGER.getTexture(colorType + "Koopa" + dir + "0");
        }
    }
}

void Koopa::attacked(Direction direction)
{
}

float Koopa::getScores() const
{
    return SCORE_STOMP_KOOPA;
}

void Koopa::stomped()
{
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
        // First stomp: Koopa becomes a stationary shell
    if (koopaState != SHELL_KOOPA) {
        koopaState = SHELL_KOOPA;
        velocity.x = 0;
        velocity.y = 0;
        setSize({ 32, 32 });
        setY(getY() + 22); // Adjust position for smaller shell size
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
        Effect* text = new TextEffect(to_string(SCORE_STOMP_KOOPA).c_str(), getCenter());
        globalGameEngine->addEffect(text);
    }
}

void Koopa::kicked(Direction direction)
{
    if (koopaState != SHELL_KOOPA || velocity.x != 0)
        return;
    // kick the shell
    this->isKicked = true;
    velocity.x = (direction == LEFT) ? KOOPA_SHELL_SPEED * 0.75 : -KOOPA_SHELL_SPEED * 0.75;
    this->direction = (direction == LEFT) ? RIGHT : LEFT;
    reviveTimer = 0.0f;
    isReviving = false;
}

void Koopa::updateCollision()
{
    if (koopaState == SHELL_KOOPA) {
        CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y });
        CollSouth.setPos({ position.x + size.x / 2 - CollSouth.getWidth() / 2, position.y + size.y - CollSouth.getHeight()});
        CollEast.setSize({ 5, size.y - 5 });
        CollEast.setPos({ position.x + size.x - CollEast.getWidth(), position.y + size.y / 2 - CollEast.getHeight() / 2 });
        CollWest.setSize({ 5, size.y - 5 });
        CollWest.setPos({ position.x, position.y + size.y / 2 - CollWest.getHeight() / 2 });
    }
    else {
        CollWest.setSize({ 5, size.y - 5 });
        CollEast.setSize({ 5, size.y - 5 });
        Entity::updateCollision();
    }
}

ENEMY_TYPE FlyingKoopa::getEnemyType() const {
    return KOOPA;
}

//FlyingKoopa::FlyingKoopa(Vector2 pos, Texture2D texture):
//    Enemy(pos, { 32, 54 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, GREEN),
//    reviveTimer(0.0f), isReviving(false), reviveShakeTimer(0.0f),
//    koopaState(NORMAL_KOOPA), koopaType(YELLOW_KOOPA)
//{
//
//}

void FlyingKoopa::Update() {

}
void FlyingKoopa::UpdateTexture() {

}
float FlyingKoopa::getScores() const {
    return SCORE_STOMP_KOOPA;
}