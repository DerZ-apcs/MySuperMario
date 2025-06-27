#include "../include/Enemy.h"
#include "../include/Mario.h"
#include <raylib.h>

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

//void Enemy::draw() {
//    if (!isDead) {
//        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
//        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
//        Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
//        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
//    }
//}

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

// Goomba Class Implementation
Goomba::Goomba(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BROWN) {
}

void Goomba::Update() {
    if (state == ON_GROUND && !isDead) {
        if (direction == LEFT) {
            velocity.x = -100;
        }
        else {
            velocity.x = 100;
        }
    }
    Enemy::Update();
}

void Goomba::draw() {
    Enemy::draw();
}

void Goomba::UpdateTexture() {
    if (isDead || state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_Dead");
        return;
    }
    if (state == ON_GROUND) {
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (direction == LEFT) {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_LEFT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_LEFT_1");
            }
        }
        else {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_RIGHT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_RIGHT_1");
            }
        }
    }
}

void Goomba::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = 0.3f;
        mario.setVelY(-300);
        mario.addScore(100);
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

void Goomba::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    if (isDead) return;
    Koopa* koopa = dynamic_cast<Koopa*>(&enemy);
    if (koopa && koopa->getState() == STATE_SHELL && (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) && koopa->getVelX() != 0) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = 0.5f;
        Singleton<ResourceManager>::getInstance().playSound("GOOMBA_SQUASH");
        updateSquashEffect();
        UpdateTexture();
    }
}

void Goomba::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = -velocity.x;
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = ON_GROUND;
    }
    else if (collType == COLLISION_TYPE_NORTH) {
        setY(tile.getY() + tile.getHeight());
        velocity.y = 0;
    }
}

// FlyingGoomba Class Implementation
FlyingGoomba::FlyingGoomba(Vector2 pos, Texture2D texture)
    : Goomba(pos, texture), jumpTimer(0.0f) {
    velocity.x = -100; // Di chuyển ngang ban đầu
    state = ON_GROUND; // Bắt đầu trên mặt đất
}

void FlyingGoomba::Update() {
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

    // Logic nhảy
    jumpTimer += deltaTime;
    if (state == ON_GROUND && jumpTimer > 1.0f) { // Nhảy mỗi 1 giây
        velocity.y = -300; // Nhảy lên
        state = JUMPING;
        jumpTimer = 0.0f;
    }

    if (state != ON_GROUND) {
        position.y += velocity.y * deltaTime;
        velocity.y += GRAVITY * deltaTime;
        if (velocity.y > 0 && state == JUMPING) {
            state = FALLING;
        }
    }

    UpdatePhysics();
    UpdateTexture();
}

void FlyingGoomba::UpdateTexture() {
    if (isDead || state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (direction == LEFT) {
        if (currFrame == 0) {
            texture = Singleton<ResourceManager>::getInstance().getTexture("FlyingGoomba_LEFT_0");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture("FlyingGoomba_LEFT_1");
        }
    }
    else {
        if (currFrame == 0) {
            texture = Singleton<ResourceManager>::getInstance().getTexture("FlyingGoomba_RIGHT_0");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture("FlyingGoomba_RIGHT_1");
        }
    }
}

void FlyingGoomba::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = 0.3f;
        mario.setVelY(-300);
        mario.addScore(100);
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

void FlyingGoomba::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = -velocity.x;
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = ON_GROUND;
        jumpTimer = 0.5f; // Delay trước khi nhảy lại
    }
    else if (collType == COLLISION_TYPE_NORTH) {
        setY(tile.getY() + tile.getHeight());
        velocity.y = 0;
    }
}

// Koopa Class Implementation
Koopa::Koopa(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, GREEN),
    reviveTimer(0.0f), isReviving(false), reviveShakeTimer(0.0f) {
}

void Koopa::Update() {
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
    if (state == ON_GROUND && !isDead) {
        if (direction == LEFT) {
            velocity.x = -80;
        }
        else {
            velocity.x = 80;
        }
        reviveTimer = 0.0f;
        isReviving = false;
        reviveShakeTimer = 0.0f;
    }
    else if (state == STATE_SHELL && !isDead) {
        if (velocity.x == 0) {
            reviveTimer += GetFrameTime();
            if (reviveTimer > 4.0f && reviveTimer < 5.0f) {
                isReviving = true;
                reviveShakeTimer += GetFrameTime();
            }
            if (reviveTimer > 5.0f) {
                state = ON_GROUND;
                setHeight(48);
                setSize({ 32, 48 });
                setY(getY() - 16);
                velocity.x = (direction == LEFT) ? -80 : 80;
                reviveTimer = 0.0f;
                isReviving = false;
                reviveShakeTimer = 0.0f;
                squashScale = 1.0f;
                updateCollision();
                Singleton<ResourceManager>::getInstance().playSound("KOOPA_REVIVE");
                UpdateTexture();
            }
        }
        else {
            reviveTimer = 0.0f;
            isReviving = false;
            reviveShakeTimer = 0.0f;
        }
    }
    Enemy::Update();
}


void Koopa::draw() {
    if (!isDead) {
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
        Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
        if (isReviving && (int)(reviveShakeTimer * 10) % 2 == 0) {
            DrawTexturePro(texture, source, dest, origin, 0.0f, Fade(WHITE, 0.5f));
        }
        else {
            DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
        }
    }
}

void Koopa::UpdateTexture() {
    if (state == STATE_SHELL || state == STATE_IS_DYING) {
        if (state == STATE_SHELL && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_Shell");
        }
        return;
    }
    if (state == ON_GROUND) {
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (direction == LEFT) {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_LEFT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_LEFT_1");
            }
        }
        else {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_RIGHT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_RIGHT_1");
            }
        }
    }
}


void Koopa::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        if (state != STATE_SHELL) {
            state = STATE_SHELL;
            velocity.x = 0;
            velocity.y = 0;
            setSize({ 32, 32 });
            setY(getY() + 16);
            reviveTimer = 0.0f;
            isReviving = false;
            reviveShakeTimer = 0.0f;
            squashScale = 1.0f;
            updateCollision();
            mario.setVelY(-300);
            mario.addScore(100);
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            UpdateTexture();
        }
        else {
            state = STATE_IS_DYING;
            velocity.x = 0;
            velocity.y = -200;
            deathTimer = 0.3f;
            mario.setVelY(-300);
            mario.addScore(200);
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            updateSquashEffect();
            UpdateTexture();
        }
    }
    else if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        if (state == STATE_SHELL) {
            if (velocity.x == 0) {
                velocity.x = (collType == COLLISION_TYPE_EAST) ? 300 : -300;
                direction = (collType == COLLISION_TYPE_EAST) ? RIGHT : LEFT;
                reviveTimer = 0.0f;
                isReviving = false;
                reviveShakeTimer = 0.0f;
                mario.setVelY(-300);
                mario.addScore(200);
                Singleton<ResourceManager>::getInstance().playSound("KICK");
                UpdateTexture();
            }
            else {
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
        else {
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
    else if (collType == COLLISION_TYPE_NORTH) {
        if (state == STATE_SHELL) {
            // Không tiêu diệt Shell, chỉ bật Mario lên
            mario.setVelY(-200);
            Singleton<ResourceManager>::getInstance().playSound("BUMP");
        }
        else {
            // Koopa bình thường gây sát thương cho Mario
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
}

void Koopa::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    if (isDead || state != STATE_SHELL || velocity.x == 0) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        enemy.CollisionWithEnemy(*this, collType);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
    }
}

void Koopa::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = -velocity.x;
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = (state == STATE_SHELL) ? STATE_SHELL : ON_GROUND;
    }
    else if (collType == COLLISION_TYPE_NORTH) {
        setY(tile.getY() + tile.getHeight());
        velocity.y = 0;
    }
}

// Bullet Class Implementation
Bullet::Bullet(Vector2 pos, Texture2D texture, Direction direction)
    : Enemy(pos, { 32, 16 }, { direction == LEFT ? -300.0f : 300.0f, 0 }, direction, FLYING, texture, 0.2f, 1, GRAY) {
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
        currFrame = (currFrame + 1) % maxFrame ;
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
    //    // Bullet bị phá hủy khi va chạm với tile ngang
    //    state = STATE_IS_DYING;
    //    velocity.x = 0;
    //    velocity.y = 0;
    //    deathTimer = 0.3f;
    //    Singleton<ResourceManager>::getInstance().playSound("STOMP");
    //    updateSquashEffect();
    //    UpdateTexture();
    //}
}