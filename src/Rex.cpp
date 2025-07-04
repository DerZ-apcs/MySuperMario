#include "../include/Rex.h"
#include "../include/Koopa.h"

// Rex Class Implementation
Rex::Rex(Vector2 pos, Texture2D texture, MediatorCollision* mediator)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BLUE),
    rexState(REX_NORMAL), detectMarioRange(250.0f), mediatorCollision(mediator), collisionTimer(0.0f) {
    velocity.x = -REX_SPEED; // REX_SPEED được định nghĩa trong Enemy.h
    updateCollision();
}

void Rex::Update() {
    if (isReadyForRemoval() || state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    const float deltaTime = GetFrameTime();

    if (collisionTimer > 0) {
        collisionTimer -= deltaTime;
    }

    Mario* mario = mediatorCollision ? mediatorCollision->GetMario() : nullptr;
    if (mario && mario->getState() != STATE_IS_DYING && collisionTimer <= 0) {
        float distance = Vector2Distance(position, mario->getPosition());
        if (distance <= detectMarioRange) {
            // Mario trong phạm vi phát hiện, thay đổi hướng và tốc độ
            if (mario->getX() < position.x) {
                direction = LEFT;
                velocity.x = (rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED;
            }
            else {
                direction = RIGHT;
                velocity.x = (rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED;
            }
        }
        else {
            // Mario ngoài phạm vi, di chuyển bình thường
            velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
                ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
        }
    }
    else {
        // Di chuyển bình thường
        velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
            ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
    }

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
            // Lần giẫm đầu: Chuyển sang trạng thái nén
            rexState = REX_COMPRESSED;
            setSize({ 24, 32 });
            setY(getY() + 16); // Điều chỉnh vị trí cho kích thước nhỏ hơn
            velocity.x = (direction == LEFT) ? -REX_COMPRESSED_SPEED : REX_COMPRESSED_SPEED;
            updateCollision();
            mario.setVelY(MARIO_BOUNCE_VELOCITY);
           // mario.addScore(SCORE_STOMP_REX);
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            UpdateTexture();
        }
        else {
            // Lần giẫm thứ hai: Chuyển sang trạng thái chết
            state = STATE_IS_DYING;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
            mario.setVelY(MARIO_BOUNCE_VELOCITY);
            //mario.addScore(SCORE_STOMP_REX);
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
    updateCollision();
    Singleton<ResourceManager>::getInstance().playSound("FIREBALL_KILL");
}

void Rex::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;

    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = (direction == LEFT) ? ((rexState == REX_NORMAL) ? -REX_SPEED : -REX_COMPRESSED_SPEED) :
            ((rexState == REX_NORMAL) ? REX_SPEED : REX_COMPRESSED_SPEED);
        collisionTimer = 0.5f; // Tạm thời vô hiệu hóa logic đuổi Mario trong 0.5 giây
        UpdateTexture();
    }
    else if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = ON_GROUND;
       // updateCollision();
    }
    else if (collType == COLLISION_TYPE_NORTH) {
        setY(tile.getY() + tile.getHeight());
        velocity.y = 0;
       // updateCollision();
    }
}

void Rex::updateCollision() {
    // Cập nhật kích thước hộp va chạm dựa trên trạng thái của Rex
    if (rexState == REX_NORMAL) {
        CollNorth.setSize({ size.x * 0.8f, 5 });
        CollSouth.setSize({ size.x * 0.8f, 5 });
        CollEast.setSize({ 5, size.y * 0.8f });
        CollWest.setSize({ 5, size.y * 0.8f });
    }
    else if (rexState == REX_COMPRESSED) {
        CollNorth.setSize({ size.x * 0.8f, 5 });
        CollSouth.setSize({ size.x * 0.8f, 5 });
        CollEast.setSize({ 5, size.y * 0.8f });
        CollWest.setSize({ 5, size.y * 0.8f });
    }

    // Cập nhật vị trí hộp va chạm (không sử dụng squashScale khi không ở trạng thái chết)
    if (state != STATE_IS_DYING) {
        squashScale = 1.0f; // Đảm bảo không áp dụng squashScale khi không chết
    }

    CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y });
    CollSouth.setPos({ position.x + size.x / 2 - CollSouth.getWidth() / 2, position.y + size.y - CollSouth.getHeight() });
    CollEast.setPos({ position.x + size.x - CollEast.getWidth(), position.y + size.y / 2 - CollEast.getHeight() / 2 });
    CollWest.setPos({ position.x, position.y + size.y / 2 - CollWest.getHeight() / 2 });

    // Cập nhật lại rect cho Entity
    rect = { position.x, position.y, size.x, size.y };
}