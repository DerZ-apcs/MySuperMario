//#include "../include/Koopa.h"
//
//// Koopa Class Implementation
//Koopa::Koopa(Vector2 pos, Texture2D texture)
//    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, GREEN),
//    reviveTimer(0.0f), isReviving(false), reviveShakeTimer(0.0f) {
//}
//
//void Koopa::Update() {
//    // Xử lý trạng thái chết
//    if (isReadyForRemoval() || state == STATE_IS_DYING) {
//        if (deathTimer > 0) {
//            deathTimer -= GetFrameTime();
//            updateSquashEffect();
//            if (deathTimer <= 0) {
//                isDead = true;
//            }
//        }
//        UpdateTexture();
//        return;
//    }
//
//    if (state == STATE_SHELL && velocity.x == 0) {
//        reviveTimer += GetFrameTime(); // Bắt đầu đếm giờ
//        if (reviveTimer > KOOPA_REVIVE_WARNING_TIME) {
//            isReviving = true;
//            reviveShakeTimer += GetFrameTime(); // Timer cho hiệu ứng nhấp nháy
//        }
//        // Khi hết giờ, hồi sinh hoàn toàn
//        if (reviveTimer > KOOPA_REVIVE_TIME) {
//            state = ON_GROUND;
//            setHeight(48);
//            setSize({ 32, 48 });
//            setY(getY() - 16); // Nâng Koopa lên để vừa với size mới
//            isReviving = false; // Tắt trạng thái cảnh báo
//            reviveTimer = 0.0f;
//            reviveShakeTimer = 0.0f;
//            updateCollision();
//            Singleton<ResourceManager>::getInstance().playSound("KOOPA_REVIVE");
//        }
//    }
//    else {
//        reviveTimer = 0.0f;
//        isReviving = false;
//        reviveShakeTimer = 0.0f;
//    }
//
//    if (state == ON_GROUND) {
//        if (direction == LEFT) {
//            velocity.x = -KOOPA_SPEED;
//        }
//        else {
//            velocity.x = KOOPA_SPEED;
//        }
//    }
//    Enemy::Update();
//}
//
//void Koopa::draw() {
//    if (!isDead) {
//        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
//        Rectangle dest = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
//        Vector2 origin = { 0, 0 };
//
//        if (isReviving && (int)(reviveShakeTimer * 10) % 2 == 0) {
//            DrawTexturePro(texture, source, dest, origin, 0.0f, Fade(WHITE, 0.5f));
//        }
//        else {
//            DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
//        }
//
//#ifdef DEBUG
//        CollNorth.draw();
//        CollSouth.draw();
//        CollEast.draw();
//        CollWest.draw();
//#endif
//    }
//}
//
//void Koopa::UpdateTexture() {
//    if (state == STATE_SHELL || state == STATE_IS_DYING) {
//        if (state == STATE_SHELL && velocity.x != 0) {
//            frameAcum += GetFrameTime();
//            if (frameAcum > 0.05f) {
//                currFrame = (currFrame + 1) % 4;
//                frameAcum = 0;
//            }
//            texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_Shell_" + std::to_string(currFrame));
//        }
//        else {
//            texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_Shell");
//        }
//        return;
//    }
//    if (state == ON_GROUND) {
//        frameAcum += GetFrameTime();
//        if (frameAcum > frameTime) {
//            currFrame = (currFrame + 1) % (maxFrame + 1);
//            frameAcum = 0;
//        }
//        if (direction == LEFT) {
//            if (currFrame == 0) {
//                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_LEFT_0");
//            }
//            else {
//                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_LEFT_1");
//            }
//        }
//        else {
//            if (currFrame == 0) {
//                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_RIGHT_0");
//            }
//            else {
//                texture = Singleton<ResourceManager>::getInstance().getTexture("Koopa_RIGHT_1");
//            }
//        }
//    }
//}
//
//void Koopa::CollisionWithCharacter(Mario& mario, CollisionType collType) {
//    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
//
//    // 1. Mario stomps from above (COLLISION_TYPE_SOUTH)
//    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING)) {
//        // First stomp: Koopa becomes a stationary shell
//        if (state != STATE_SHELL) {
//            state = STATE_SHELL;
//            velocity.x = 0;
//            velocity.y = 0;
//            setSize({ 32, 32 });
//            setY(getY() + 16); // Adjust position for smaller shell size
//            updateCollision();
//            mario.addScore(SCORE_STOMP_KOOPA);
//            Singleton<ResourceManager>::getInstance().playSound("STOMP");
//            reviveTimer = 0.0f;
//            isReviving = false;
//        }
//        // Second stomp: Shell disappears
//        else {
//            state = STATE_IS_DYING;
//            velocity.y = -250; // Slight upward bounce
//            velocity.x = (rand() % 100) - 50; // Random horizontal velocity
//            deathTimer = ENEMY_DEATH_TIMER_LONG; // Disappear after 0.5s
//            mario.addScore(SCORE_KICK_KOOPA);
//            Singleton<ResourceManager>::getInstance().playSound("KICK");
//        }
//        mario.setVelY(MARIO_BOUNCE_VELOCITY); // Mario bounces up
//        UpdateTexture();
//        return;
//    }
//
//    // 2. Mario collides from the side (COLLISION_TYPE_EAST or WEST)
//    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
//        if (state == STATE_SHELL) {
//            // Stationary shell gets kicked
//            if (velocity.x == 0) {
//                velocity.x = (collType == COLLISION_TYPE_EAST) ? KOOPA_SHELL_SPEED : -KOOPA_SHELL_SPEED;
//                direction = (collType == COLLISION_TYPE_EAST) ? RIGHT : LEFT;
//                mario.addScore(SCORE_KICK_KOOPA);
//                Singleton<ResourceManager>::getInstance().playSound("KICK");
//                reviveTimer = 0.0f;
//                isReviving = false;
//                UpdateTexture();
//            }
//            // Moving shell hurts Mario
//            else if (mario.getInvincibilityTimer() <= 0) {
//                mario.TransitionToSmall();
//                mario.setInvincibilityTimer(2.0f);
//            }
//        }
//        // Non-shell Koopa hurts Mario
//        else if (mario.getInvincibilityTimer() <= 0) {
//            mario.TransitionToSmall();
//            mario.setInvincibilityTimer(2.0f);
//        }
//        return;
//    }
//
//    // 3. Mario collides from below (COLLISION_TYPE_NORTH)
//    if (collType == COLLISION_TYPE_NORTH && mario.getInvincibilityTimer() <= 0) {
//        mario.TransitionToSmall();
//        mario.setInvincibilityTimer(2.0f);
//    }
//}
//
//void Koopa::CollisionWithEnemy(Enemy& enemy, CollisionType collType) {
//    if (isDead || state != STATE_SHELL || velocity.x == 0) return;
//    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
//        enemy.CollisionWithEnemy(*this, collType);
//        Singleton<ResourceManager>::getInstance().playSound("STOMP");
//    }
//}
//
//void Koopa::CollisionWithFireball(FireBall& fireball) {
//    if (isDead || state == STATE_IS_DYING) return;
//    state = STATE_IS_DYING;
//    velocity.y = -250; // Nhảy lên nhẹ
//    velocity.x = (rand() % 100) - 50; // Văng ngang ngẫu nhiên
//    deathTimer = ENEMY_DEATH_TIMER_LONG;
//    updateCollision();
//    Singleton<ResourceManager>::getInstance().playSound("FIREBALL_KILL");
//    // Giả định Mario được truy cập qua MediatorCollision hoặc cách khác
//    // mario->addScore(SCORE_FIREBALL_KOOPA); // Cần thêm cơ chế truyền Mario
//}
//
//void Koopa::HandleTileCollision(const Tile& tile, CollisionType collType) {
//    if (isDead || state == STATE_IS_DYING) return;
//    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
//        direction = (direction == LEFT) ? RIGHT : LEFT;
//        if (collType == COLLISION_TYPE_EAST) {
//            setX(tile.getX() - getWidth());
//        }
//        else if (collType == COLLISION_TYPE_WEST) {
//            setX(tile.getX() + tile.getWidth());
//        }
//        velocity.x = -velocity.x;
//        UpdateTexture();
//    }
//    else if (collType == COLLISION_TYPE_SOUTH) {
//        setY(tile.getY() - getHeight());
//        velocity.y = 0;
//        state = (state == STATE_SHELL) ? STATE_SHELL : ON_GROUND;
//    }
//    else if (collType == COLLISION_TYPE_NORTH) {
//        setY(tile.getY() + tile.getHeight());
//        velocity.y = 0;
//    }
//}
