#include "../include/Goomba.h"
#include "../include/Koopa.h"

// Goomba Class Implementation
Goomba::Goomba(Vector2 pos, Texture2D texture, MediatorCollision* mediator)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, BROWN),
    pauseTimer(0.0f), isPaused(false), detectMarioRange(200.0f), mediatorCollision(mediator), collisionTimer(0.0f) {
    velocity.x = -GOOMBA_SPEED;
}

void Goomba::Update() {
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
            if (mario->getX() < position.x) {
                direction = LEFT;
                velocity.x = -GOOMBA_SPEED * 1.5f; 
            }
            else {
                direction = RIGHT;
                velocity.x = GOOMBA_SPEED * 1.5f; 
            }
        }
        else {
            // Mario ngoài phạm vi, di chuyển bình thường
            if (state == ON_GROUND) {
                velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
            }
        }
    }
    else {
        if (isPaused) {
            pauseTimer -= deltaTime;
            if (pauseTimer <= 0) {
                isPaused = false;
                direction = (direction == LEFT) ? RIGHT : LEFT;
                velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
            }
            velocity.x = 0;
        }
        else {
            if (state == ON_GROUND) {
                if (collisionTimer <= 0) {
                    velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
                }
                if (GetRandomValue(0, 1000) < 3) { // 0.3% cơ hội dừng lại
                    isPaused = true;
                    pauseTimer = GetRandomValue(5, 15) / 10.0f; // Dừng 0.5-1.5 giây
                }
            }
        }
    }
    Enemy::Update();
}

void Goomba::draw() {
    Enemy::draw();
}

void Goomba::UpdateTexture() {
    if (state == STATE_IS_DYING) {
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
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Goomba_LEFT_0" : "Goomba_LEFT_1");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "Goomba_RIGHT_0" : "Goomba_RIGHT_1");
        }
    }
}

void Goomba::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        state = STATE_IS_DYING;
        velocity.x = 0.0f; // Hiệu ứng đẩy nhẹ
        velocity.y = 0.0f; // Nhảy nhẹ lên
        deathTimer = 0.3f;
        mario.setVelY(MARIO_BOUNCE_VELOCITY);
        mario.addScore(SCORE_STOMP_GOOMBA);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        updateSquashEffect();
        UpdateTexture();
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

void Goomba::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
    if (isDead) return;
    Koopa* koopa = dynamic_cast<Koopa*>(&enemy);
    if (koopa && koopa->getState() == STATE_SHELL && (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) && koopa->getVelX() != 0) {
        state = STATE_IS_DYING;
        velocity.x = 0.0f; // Đẩy ra xa
        velocity.y = 0.0f;
        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
        Singleton<ResourceManager>::getInstance().playSound("GOOMBA_SQUASH");
        updateSquashEffect();
        UpdateTexture();
        return;
    }
}

void Goomba::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED;
        collisionTimer = 0.5f; // Tạm thời vô hiệu hóa logic đuổi Mario trong 0.5 giây
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
FlyingGoomba::FlyingGoomba(Vector2 pos, Texture2D texture, MediatorCollision* mediator)
    : Goomba(pos, texture, mediator), jumpTimer(0.0f), detectMarioRange(250.0f),
    collisionTimer(0.0f), hasWings(true),isSearchPaused(false), searchCooldownTimer(0.0f) {
    velocity.x = -FLYINGGOOMBA_SPEED;
    state = ON_GROUND;
}

void FlyingGoomba::Update() {

    if (!hasWings) {
        Goomba::Update();
        return;
    }

    if (isReadyForRemoval() || state == STATE_IS_DYING) {
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

    if (isSearchPaused) {
        searchCooldownTimer -= deltaTime;
        if (searchCooldownTimer <= 0) {
            isSearchPaused = false; 
        }
    }

    if (collisionTimer > 0) {
		collisionTimer -= deltaTime;
    }

    bool shouldChase = false;
    Mario* mario = mediatorCollision ? mediatorCollision->GetMario() : nullptr;
    if (mario && !isSearchPaused && mario->getState() != STATE_IS_DYING && collisionTimer <= 0) {
        float totalDistance = Vector2Distance(position, mario->getPosition());

        if (totalDistance <= detectMarioRange) {
            float horizontalDistance = fabsf(mario->getX() - this->position.x);
            const float horizontalDeadZone = 2.0f; // Vùng chết theo chiều ngang

            if (horizontalDistance < horizontalDeadZone) {
                // Bị kẹt theo chiều ngang -> Bắt đầu tạm nghỉ tìm kiếm
                isSearchPaused = true;
                searchCooldownTimer = 2.0f; // Tạm nghỉ 2 giây
                shouldChase = false;        // Buộc quay về hành vi Tuần tra
            }
            else {
                shouldChase = true;
            }
        }
    }

    // --- 3. Thiết lập vận tốc dựa trên hành vi ---
    if (shouldChase) {
        // Hành vi Đuổi theo
        if (mario->getX() < position.x) {
            direction = LEFT;
            velocity.x = -FLYINGGOOMBA_SPEED * 1.5f;
        }
        else {
            direction = RIGHT;
            velocity.x = FLYINGGOOMBA_SPEED * 1.5f;
        }
    }
    else {
        // Hành vi Tuần tra (mặc định)
        velocity.x = (direction == LEFT) ? -FLYINGGOOMBA_SPEED : FLYINGGOOMBA_SPEED;
    }

    // --- 4. Logic nhảy ---
    jumpTimer += deltaTime;
    float currentJumpInterval = shouldChase ? (FLYINGGOOMBA_JUMP_INTERVAL * 0.7f) : FLYINGGOOMBA_JUMP_INTERVAL;

    if (state == ON_GROUND && jumpTimer > currentJumpInterval) {
        velocity.y = -FLYINGGOOMBA_JUMP_VELOCITY;
        state = JUMPING;
        jumpTimer = 0.0f;
    }

    // Hiệu ứng bay lượn
    static float hoverTimer = 0.0f;
    hoverTimer += deltaTime;
    position.y += sin(hoverTimer * 3.0f) * 50.0f * deltaTime;

    // --- 5. Cập nhật vật lý và hình ảnh ---
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Áp dụng trọng lực
    if (state != ON_GROUND) {
        velocity.y += GRAVITY * deltaTime * 0.5f;
        if (velocity.y > 0 && state == JUMPING) {
            state = FALLING;
        }
    }

    UpdatePhysics();
    UpdateTexture();
}

void FlyingGoomba::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;

    // Handle Mario stomping on the Flying Goomba
    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
        if (hasWings) {
            hasWings = false; // Lose wings
            state = FALLING; // Fall to the ground
            position.y += 16.0f;
            velocity.x = (direction == LEFT) ? -GOOMBA_SPEED : GOOMBA_SPEED; // Set to normal Goomba speed
            velocity.y = 0; // Reset vertical velocity before bounce
            mario.setVelY(MARIO_BOUNCE_VELOCITY);
            mario.addScore(SCORE_STOMP_GOOMBA); // Give score for de-winging
            Singleton<ResourceManager>::getInstance().playSound("STOMP");
            this->mediatorCollision = nullptr;
        }
        else {
            // If wings are already gone, call the base Goomba collision, which handles death
            Goomba::CollisionWithCharacter(mario, collType);
        }
    }
    // For any other collision, Mario gets hurt. Call the base Goomba logic.
    else if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST || collType == COLLISION_TYPE_NORTH) {
        Goomba::CollisionWithCharacter(mario, collType);
    }
}

void FlyingGoomba::UpdateTexture() {

    if (!hasWings) {
        Goomba::UpdateTexture();
        return;
    }

    if (state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Goomba_Dead");
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }

    if (direction == LEFT) {
        texture = Singleton<ResourceManager>::getInstance().getTexture(
            currFrame == 0 ? "FlyingGoomba_LEFT_0" : "FlyingGoomba_LEFT_1");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture(
            currFrame == 0 ? "FlyingGoomba_RIGHT_0" : "FlyingGoomba_RIGHT_1");
    }
}

void FlyingGoomba::HandleTileCollision(const Tile& tile, CollisionType collType) {
    
    if (!hasWings) {
        Goomba::HandleTileCollision(tile, collType);
        return;
    }

    if (isDead || state == STATE_IS_DYING) return;
    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST) {
            setX(tile.getX() - getWidth());
        }
        else if (collType == COLLISION_TYPE_WEST) {
            setX(tile.getX() + tile.getWidth());
        }
        velocity.x = (direction == LEFT) ? -FLYINGGOOMBA_SPEED : FLYINGGOOMBA_SPEED;
        collisionTimer = 1.0f; 
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
