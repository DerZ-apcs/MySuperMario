#include "../include/Rex.h"
#include "../include/Koopa.h"

// Rex Class Implementation
Rex::Rex(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BLUE),
    rexState(REX_NORMAL) {
    velocity.x = -REX_SPEED; 
}

void Rex::Update() {
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    const float deltaTime = GetFrameTime();

    velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
    ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);

    Enemy::Update();
}

void Rex::draw() {
    Enemy::draw();
}

void Rex::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Rex_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (rexState == REX_NORMAL) {
        if (direction == LEFT) {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Rex_LEFT_0" : "Rex_LEFT_1");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Rex_RIGHT_0" : "Rex_RIGHT_1");
        }
    }
    else {
        if (direction == LEFT) {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Rex_Compressed_LEFT_0" : "Rex_Compressed_LEFT_1");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Rex_Compressed_RIGHT_0" : "Rex_Compressed_RIGHT_1");
        }
    }
}

void Rex::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;

    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        if (rexState == REX_NORMAL) {
            rexState = REX_COMPRESSED;
            setSize({ 32, 32 });
            setY(getY() + 16); // Điều chỉnh vị trí cho kích thước nhỏ hơn
            if (direction == RIGHT) direction = LEFT;
            else direction = RIGHT;
            velocity.x = (direction == LEFT) ? -REX_COMPRESSED_SPEED : REX_COMPRESSED_SPEED;
            mario.setVelY(MARIO_BOUNCE_VELOCITY);
            mario.addScore(SCORE_STOMP_REX);
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            UpdateTexture();
        }
        else {
            state = STATE_IS_DYING;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
            mario.setVelY(MARIO_BOUNCE_VELOCITY);
            mario.addScore(SCORE_STOMP_REX);
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            updateSquashEffect();
            UpdateTexture();
        }
        return;
    }

    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) {
        if (mario.getMarioState() == STATE_SUPER || mario.getMarioState() == STATE_FIRE_BALL) {
            mario.TransitionToSmall();
            mario.setInvincibilityTimer(1.0f);
        }
        else {
            mario.setState(STATE_IS_DYING);
            Singleton<ResourceManager>::getInstance().playSound("MARIO_DIE");
        }
    }
}

void Rex::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;

    Koopa* koopa = dynamic_cast<Koopa*>(&enemy);
    if (koopa && koopa->getState() == STATE_SHELL && (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) && koopa->getVelX() != 0) {
        state = STATE_IS_DYING;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
    }
}

void Rex::CollisionWithFireball(FireBall& fireball) {
    if (isDead || state == STATE_IS_DYING) return;
    state = STATE_IS_DYING;
    velocity.y = -250; // Nhảy lên nhẹ
    velocity.x = (rand() % 100) - 50; // Văng ngang ngẫu nhiên
    deathTimer = ENEMY_DEATH_TIMER_LONG;
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL_KILL");
}

void Rex::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;

    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth() - 0.1f);
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth() + 0.1f);
        }
        velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
            ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
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
