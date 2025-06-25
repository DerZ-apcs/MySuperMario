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

void Enemy::draw() {
    if (!isDead) {
        // Vẽ với hiệu ứng nén
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
        Vector2 origin = { (texture.width * squashScale) / 2, (texture.height * squashScale) / 2 };
        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
    }
}

void Enemy::updateSquashEffect() {
    if (state == STATE_IS_DYING) {
        squashScale = 1.0f - (0.5f - deathTimer) / 0.5f; // Nén từ 1.0 xuống 0.0 trong 0.5s
        // Chỉ cập nhật kích thước va chạm, không thay đổi kích thước thực của texture
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
    // Cập nhật vùng va chạm với hiệu ứng nén
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

void Goomba::Update() { // Note đại
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
    if (isDead) return;
    if (collType == COLLISION_TYPE_SOUTH) {
        state = STATE_IS_DYING;
        velocity.x = 0;
        velocity.y = 0;
        deathTimer = 0.5f; // Hiển thị hiệu ứng nén trong 0.5 giây
        mario.setVelY(-200); // Mario bật lên
        mario.addScore(100); // Thêm điểm
        Singleton<ResourceManager>::getInstance().playSound("PLAYER_JUMP");
        updateSquashEffect();
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) {
        if (mario.getState() == STATE_SUPER || mario.getState() == STATE_FIRE_BALL) {
            mario.TransitionToSmall();
        }
        else {
            // Mario nhỏ chịu sát thương (có thể thêm logic game over)
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

// Koopa Class Implementation
Koopa::Koopa(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, GREEN), reviveTimer(0.0f) {
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
            velocity.x = -80; // Test
        }
        else {
            velocity.x = 80;
        }
        reviveTimer = 0.0f;
    }
    else if (state == STATE_SHELL && !isDead) {
        if (velocity.x == 0) {
            reviveTimer += GetFrameTime();
            if (reviveTimer > 5.0f) { // Hồi sinh sau 5 giây
                state = ON_GROUND;
                setHeight(48);
                setSize({ 32, 48 }); // Reset kích thước
                velocity.x = (direction == LEFT) ? -80 : 80;
                reviveTimer = 0.0f;
                squashScale = 1.0f; // Reset nén
                updateCollision();
                UpdateTexture();
            }
        }
        else {
            reviveTimer = 0.0f;
        }
    }
    Enemy::Update();
}

void Koopa::draw() {
    Enemy::draw();
}

void Koopa::UpdateTexture() {
    if (state == STATE_SHELL || state == STATE_IS_DYING) {
        if (state == STATE_SHELL && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.1f) {
                currFrame = (currFrame + 1) % 4; // 4 frame xoay
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
    if (collType == COLLISION_TYPE_SOUTH) {
        if (state != STATE_SHELL) {
            state = STATE_SHELL;
            velocity.x = 0;
            velocity.y = 0;
            setSize({ 32, 32 }); // Shell nhỏ hơn
            reviveTimer = 0.0f;
            squashScale = 1.0f; // Reset nén
            updateCollision();
            mario.setVelY(-200);
            mario.addScore(200);
            Singleton<ResourceManager>::getInstance().playSound("PLAYER_JUMP");
            UpdateTexture();
        }
        else {
            state = STATE_IS_DYING;
            velocity.x = 0;
            velocity.y = 0;
            deathTimer = 0.5f;
            mario.setVelY(-200);
            mario.addScore(200);
            Singleton<ResourceManager>::getInstance().playSound("PLAYER_JUMP");
            updateSquashEffect();
            UpdateTexture();
        }
    }
    else if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) {
        if (state == STATE_SHELL) {
            velocity.x = (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_NORTH) ? 200 : -200;
            direction = (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_NORTH) ? RIGHT : LEFT;
            mario.setVelY(-200);
            mario.addScore(50);
            Singleton<ResourceManager>::getInstance().playSound("PLAYER_JUMP");
            UpdateTexture();
        }
        else {
            if (mario.getState() == STATE_SUPER || mario.getState() == STATE_FIRE_BALL) {
                mario.TransitionToSmall();
            }
            else {
                // Mario nhỏ chịu sát thương (có thể thêm logic game over)
            }
        }
    }
}

void Koopa::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    if (isDead || state != STATE_SHELL || velocity.x == 0) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        enemy.CollisionWithEnemy(*this, collType); // Gọi ngược lại để xử lý
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