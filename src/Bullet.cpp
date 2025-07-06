#include "../include/Bullet.h"

// Bullet Class Implementation
Bullet::Bullet(Vector2 pos, Texture2D texture, Direction direction)
    : Enemy(pos, { 32, 32 }, { direction == LEFT ? -BULLET_SPEED : BULLET_SPEED, 0 }, direction, FLYING, texture, 0.2f, 1, GRAY) {
}

Bullet::~Bullet() {
    for (auto fireball : fireballs) {
        delete fireball;
    }
    fireballs.clear();
}

void Bullet::Update() {
    if (isDead || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                isDead = true;
            }
        }
        UpdateTexture();
        return;
    }

    const float deltaTime = GetFrameTime();
    position.x += velocity.x * deltaTime;
    // Bullet không chịu trọng lực, giữ trạng thái FLYING
    UpdatePhysics();
    UpdateTexture();
}

void Bullet::draw() {
    if (!isDead)
        Enemy::draw();
    for (auto fireball : fireballs) {
        if (!fireball->IsDestroyed()) {
            fireball->draw();
        }
    }
}

void Bullet::UpdateTexture() {
    if (isDead || state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Bullet_Dead");
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % maxFrame;
        frameAcum = 0;
    }
    if (direction == LEFT) {
        texture = Singleton<ResourceManager>::getInstance().getTexture(currFrame == 0 ? "Bullet_LEFT_0" : "Bullet_LEFT_1");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture(currFrame == 0 ? "Bullet_RIGHT_0" : "Bullet_RIGHT_1");
    }
}

void Bullet::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING || mario.getInvincibilityTimer() > 0) return;
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        mario.setVelY(MARIO_BOUNCE_VELOCITY);
        mario.addScore(SCORE_STOMP_BULLET);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) {
        if (mario.getMarioState() == STATE_SUPER || mario.getMarioState() == STATE_FIRE_BALL) {
            mario.TransitionToSmall();
            mario.setInvincibilityTimer(2.0f);
        }
        else {
            mario.setState(STATE_IS_DYING);
            Singleton<ResourceManager>::getInstance().playSound("MARIO_DIE");
        }
    }
}

void Bullet::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    // Bullet không va chạm với enemy khác
}

void Bullet::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = 0.3f;
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
    }
}

void Bullet::ShootFireBall() {
    // Không làm gì vì Bullet cơ bản không bắn fireball
}

// FireBullet Class Implementation
const float FireBullet::FIREBALL_INTERVAL = 0.75f; // Bắn mỗi 0.75s
const float FireBullet::DETECTION_RANGE = 300.0f; // Phát hiện Mario trong 300 pixel

FireBullet::FireBullet(Vector2 pos, Texture2D texture, Direction direction, Mario& mario)
    : Bullet(pos, texture, direction), fireBallTimer(0.0f), mario(mario) {
}

void FireBullet::Update() {
    if (isDead || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                isDead = true;
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

    for (auto fireball : fireballs) {
        if (!fireball->IsDestroyed()) {
            fireball->Update();
        }
    }

    fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](EnemyFireBall* fireball) {
        if (fireball && (fireball->isMaxDistance() || fireball->IsDestroyed())) {
            delete fireball;
            return true;
        }
        return false;
        }), fireballs.end());

    UpdatePhysics();
    UpdateTexture();
}

void FireBullet::ShootFireBall() {
    if (fireballs.size() >= MAX_FIREBALLS) return; // Không bắn nếu vượt giới hạn
    float distanceToMario = Vector2Distance(position, mario.getPosition());
    bool isHoming = (distanceToMario <= DETECTION_RANGE);
    Direction dir = (mario.getX() > position.x) ? RIGHT : LEFT;
    Vector2 fireBallPos = { position.x + (dir == RIGHT ? size.x / 2 : -size.x / 2), position.y + size.y / 2 };
    Vector2 fireBallVel = (dir == RIGHT) ? Vector2{ 400.0f, -200.0f } : Vector2{ -400.0f, -200.0f };
    EnemyFireBall* fireball = new EnemyFireBall(fireBallPos, { 16, 16 }, fireBallVel, dir, 2.0f, &mario, isHoming);
    fireballs.push_back(fireball);
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL");
}
