#include "../include/Goomba.h"
#include "../include/Koopa.h"

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
