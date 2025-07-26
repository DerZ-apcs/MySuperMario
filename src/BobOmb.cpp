#include "../include/BobOmb.h"
#include "../include/ResourceManager.h"
#include <raymath.h>

BobOmb::BobOmb(Vector2 pos, Texture2D texture, MediatorCollision* mediator)
    : Enemy(pos, { 32, 48 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, DARKGRAY),
    isActivated(false),
    fuseTimer(BOBOMB_FUSE_TIME),
    mediatorCollision(mediator) {
    velocity.x = -BOBOMB_WALK_SPEED;
}

BobOmb::~BobOmb() {}

void BobOmb::Update() {
    // Nếu đang trong quá trình chết (nổ), hãy để lớp cha xử lý
    if (state == STATE_IS_DYING) {
        Enemy::Update();
        return;
    }

    if (isActivated) {
        // Đã được kích hoạt, bắt đầu đếm ngược
        velocity.x = 0; // Dừng di chuyển
        fuseTimer -= GetFrameTime();
        if (fuseTimer <= 0) {
            Explode();
        }
    }
    else {
        // Hành vi đi bộ bình thường, tương tự Goomba
        Enemy::Update();
    }

    // Cập nhật vật lý và texture
    UpdatePhysics();
    UpdateTexture();
}

void BobOmb::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("BobOmb_Explosion");
        return;
    }

    if (isActivated) {
        frameAcum += GetFrameTime() * 5; // Nhấp nháy nhanh hơn
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % 2;
            frameAcum = 0;
        }
        texture = (currFrame == 0)
            ? Singleton<ResourceManager>::getInstance().getTexture("BobOmb_Activated_0")
            : Singleton<ResourceManager>::getInstance().getTexture("BobOmb_Activated_1");
    }
    else {
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (direction == LEFT) {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "BobOmb_LEFT_0" : "BobOmb_LEFT_1");
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture(
                currFrame == 0 ? "BobOmb_RIGHT_0" : "BobOmb_RIGHT_1");
        }
    }
}

void BobOmb::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (isDying()) return;

    if (collType == COLLISION_TYPE_SOUTH && (mario.getState() == JUMPING || mario.getState() == FALLING) && !isActivated) {
        // Mario dẫm lên để kích hoạt
        isActivated = true;
        velocity.x = 0;
        mario.setVelY(MARIO_BOUNCE_VELOCITY);
        Singleton<ResourceManager>::getInstance().playSound("STOMP"); // Có thể thay bằng âm thanh đốt ngòi
    }
    else if (collType != COLLISION_TYPE_NONE) {
        // Nếu va chạm theo cách khác, Mario bị thương
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

void BobOmb::CollisionWithFireball(FireBall& fireball) {
    if (isDying()) return;
    Explode(); // Nổ ngay khi bị bắn
    fireball.destroy();
}

void BobOmb::HandleTileCollision(const Tile& tile, CollisionType collType) {
	if (state == STATE_IS_DYING) return;

    if (isActivated) {
        if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
            Explode();
            return;
        }
        if (collType == COLLISION_TYPE_SOUTH) {
            setY(tile.getY() - getHeight());
            velocity.y = 0;
            state = ON_GROUND;
        }
        return;
    }

    if (collType == COLLISION_TYPE_EAST || collType == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT) ? RIGHT : LEFT;
        if (collType == COLLISION_TYPE_EAST)
            setX(tile.getX() - getWidth());
        else
            setX(tile.getX() + tile.getWidth());
        velocity.x = (direction == LEFT) ? -BOBOMB_WALK_SPEED : BOBOMB_WALK_SPEED;
    }
    else if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = ON_GROUND;
    }
}

void BobOmb::Explode() {
    if (state == STATE_IS_DYING) return;

    state = STATE_IS_DYING;
    deathTimer = BOBOMB_EXPLOSION_DURATION;
    velocity = { 0, 0 };
    Singleton<ResourceManager>::getInstance().playSound("ENEMY_EXPLOSION"); // Cần thêm âm thanh này

    Mario* mario = mediatorCollision->GetMario();
    if (mario) {
        float distance = Vector2Distance(position, mario->getPosition());
        if (distance <= BOBOMB_EXPLOSION_RADIUS) {
            mario->TakeDamage();
        }
    }
}
