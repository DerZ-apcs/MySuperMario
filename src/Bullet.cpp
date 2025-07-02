#include "../include/Bullet.h"

// Bullet Class Implementation
Bullet::Bullet(Vector2 pos, Texture2D texture, Direction direction)
    : Enemy(pos, { 32, 32 }, { direction == LEFT ? -300.0f : 300.0f, 0 }, direction, FLYING, texture, 0.2f, 1, GRAY) {
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
        deathTimer = 0.3f;
        mario.setVelY(-300);
        mario.addScore(200);
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
    //if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
    //    state = STATE_IS_DYING;
    //    velocity.x = 0;
    //    velocity.y = 0;
    //    deathTimer = 0.3f;
    //    Singleton<ResourceManager>::getInstance().playSound("STOMP");
    //    updateSquashEffect();
    //    UpdateTexture();
    //}
}