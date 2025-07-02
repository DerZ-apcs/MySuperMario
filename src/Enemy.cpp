#include "../include/Enemy.h"
#include "../include/Mario.h"
#include <raylib.h>
#include <raymath.h>

// Enemy Class Implementation
Enemy::Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction direction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color)
    : Entity(pos, size, vel, direction, state, texture, frameTime, maxFrame, color), deathTimer(0.0f), isDead(false), squashScale(1.0f) {
    CollEast.setColor(BLACK);
    CollSouth.setColor(GREEN);
    CollNorth.setColor(RED);
    CollWest.setColor(PURPLE);
}

Enemy::~Enemy() {}

void Enemy::Update() {
    if (isDead || state == STATE_IS_DYING) {
        if (deathTimer > 0) {
            deathTimer -= GetFrameTime();
            updateSquashEffect();
            if (deathTimer <= 0) {
                isDead = true; // Mark for removal
            }
        }
        UpdateTexture();
        return;
    }
    const float deltaTime = GetFrameTime();
    position.x += velocity.x * deltaTime;
    if (state != ON_GROUND && state != STATE_SHELL) {
        position.y += velocity.y * deltaTime;
        velocity.y += GRAVITY * deltaTime;
        if (velocity.y > 0 && state == JUMPING) {
            state = FALLING;
        }
    }
    UpdatePhysics();
    UpdateTexture();
}

void Enemy::draw() {
    if (!isDead) {
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
        Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
#ifdef DEBUG
        CollNorth.draw();
        CollSouth.draw();
        CollEast.draw();
        CollWest.draw();
#endif
    }
}

void Enemy::updateSquashEffect() {
    if (state == STATE_IS_DYING) {
        squashScale = 1.0f - (0.5f - deathTimer) / 0.5f;
        updateCollision();
    }
}

void Enemy::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    // Virtual method, implemented in derived classes
}

void Enemy::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    // Virtual method, implemented in derived classes
}

bool Enemy::isDying() {
    return isDead || state == STATE_IS_DYING;
}

bool Enemy::isReadyForRemoval() {
    return isDead;
}

void Enemy::updateCollision() {
    CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y });
    CollSouth.setPos({ position.x + size.x / 2 - CollSouth.getWidth() / 2, position.y + size.y * squashScale - CollSouth.getHeight() });
    CollEast.setPos({ position.x + size.x * squashScale - CollEast.getWidth(), position.y + size.y * squashScale / 2 - CollEast.getHeight() / 2 });
    CollWest.setPos({ position.x, position.y + size.y * squashScale / 2 - CollWest.getHeight() / 2 });
}

void Enemy::UpdateTexture() {
    // Virtual method, implemented in derived classes
}

void Enemy::HandleTileCollision(const Tile& tile, CollisionType collType) {
    // Virtual method, implemented in derived classes
}

