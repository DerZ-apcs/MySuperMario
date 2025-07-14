#include "../include/Bullet.h"
#include "../include/GameEngine.h"

// Bullet Class Implementation
Bullet::Bullet(Vector2 pos, Texture2D texture, Direction direction)
    : Enemy(pos, { 32, 28 }, { direction == LEFT ? -BULLET_SPEED : BULLET_SPEED, 0 }, direction, FLYING, texture, 0.2f, 1, GRAY) {
}

Bullet::~Bullet() {

}

ENEMY_TYPE Bullet::getEnemyType() const
{
    return BULLET;
}

float Bullet::getScores() const
{
    return SCORE_STOMP_BULLET;
}

void Bullet::Update() {
    Entity::Update();
    if (isDead() || state == STATE_IS_DYING) {
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
    position.x += velocity.x * deltaTime;
    // Bullet không chịu trọng lực, giữ trạng thái FLYING
    Entity::updateCollision();
    UpdateTexture();
}

void Bullet::draw() {
    Enemy::draw();
}

void Bullet::UpdateTexture() {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Bullet_Dead");
        return;
    }
    std::string dir = direction == RIGHT ? "RIGHT" : "LEFT";
    texture = RESOURCE_MANAGER.getTexture("Bullet_" + dir);
}

void Bullet::stomped() {
    if (isDead() || state == STATE_IS_DYING)
        return;
    state = STATE_IS_DYING;
    velocity = { 0.f, 0.f };
    deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
    updateSquashEffect();
    UpdateTexture();
    Effect* text = new TextEffect(to_string(SCORE_STOMP_BULLET).c_str(), getCenter());
    globalGameEngine->addEffect(text);
}

void Bullet::ShootFireBall() {
    // Không làm gì vì Bullet cơ bản không bắn fireball
}

// FireBullet Class Implementation
const float FireBullet::FIREBALL_INTERVAL = 0.75f; // Bắn mỗi 0.75s
const float FireBullet::DETECTION_RANGE = 300.0f; // Phát hiện Mario trong 300 pixel

FireBullet::FireBullet(Vector2 pos, Texture2D texture, Direction direction)
    : Bullet(pos, texture, direction), fireBallTimer(0.0f) {
}

void FireBullet::Update() {
    Entity::Update();
    if (isDead() || state == STATE_IS_DYING) {
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
    position.x += velocity.x * deltaTime;
    fireBallTimer += deltaTime;
    if (fireBallTimer >= FIREBALL_INTERVAL) {
        ShootFireBall();
        fireBallTimer = 0.0f;
    }

    Entity::updateCollision();
    UpdateTexture();
}

void FireBullet::ShootFireBall() {
    //if (size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    Character* character = globalGameEngine->getCharacter() ? globalGameEngine->getCharacter() : nullptr;
    if (!character) return;

    float distanceToMario = Vector2Distance(position, character->getPosition());
    bool isHoming = (distanceToMario <= DETECTION_RANGE);
    
    Direction dir = (character->getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x + (dir == RIGHT ? size.x / 2 : -size.x / 2), position.y + size.y / 2 };
    Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 400.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
    
    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, isHoming);
    globalGameEngine->addEnemyFireBall(fireball);
    RESOURCE_MANAGER.playSound("fireball.wav");
}
