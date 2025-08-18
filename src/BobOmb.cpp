#include "../include/BobOmb.h"
#include "../include/ResourceManager.h"
#include "../include/GameEngine.h"
#include <raymath.h>


BobOmb::BobOmb(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 24, 30 }, { 0, 0 }, LEFT, ON_GROUND, texture, 0.2f, 1, DARKGRAY),
    isActivated(false),
    fuseTimer(BOBOMB_FUSE_TIME) 
{
    velocity.x = -BOBOMB_WALK_SPEED;
    scores = 100.f;
}

BobOmb::~BobOmb() {}

ENEMY_TYPE BobOmb::getEnemyType() const
{
    return BOBOMB;
}

void BobOmb::Update() {
    Entity::Update();
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

    // Cập nhật vị trí
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
	if (gravityAvailable) velocity.y += GRAVITY * GetFrameTime();
    // Cập nhật vật lý và texture
    Enemy::updateCollision();
    UpdateTexture();
}

void BobOmb::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        // Trạng thái nổ
        texture = RESOURCE_MANAGER.getTexture("BobOmb_Explosion");
        return;
    }

    if (isActivated) {
        // Trạng thái kích hoạt, nhấp nháy
        // (Sử dụng frame hiện tại để tạo hiệu ứng nhấp nháy đơn giản)
        frameAcum += GetFrameTime() * 5; // Nhấp nháy nhanh hơn
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % 2;
            frameAcum = 0;
        }
        texture = (currFrame == 0)
            ? RESOURCE_MANAGER.getTexture("BobOmb_Activated_0")
			: RESOURCE_MANAGER.getTexture(""); // sử dụng texture giả để tạo hiệu ứng nhấp nháy
    }
    else {
        // Trạng thái đi bộ
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (state == ON_GROUND) {
            if (direction == LEFT) {
                texture = RESOURCE_MANAGER.getTexture(
                    currFrame == 0 ? "BobOmb_LEFT_0" : "BobOmb_LEFT_1");
            }
            else {
                texture = RESOURCE_MANAGER.getTexture(
                    currFrame == 0 ? "BobOmb_RIGHT_0" : "BobOmb_RIGHT_1");
            }
        }
        else if (state == FALLING || state == JUMPING) {
            texture = direction == LEFT ? RESOURCE_MANAGER.getTexture("BobOmb_LEFT_0") : RESOURCE_MANAGER.getTexture("BobOmb_RIGHT_0");
        }
    }
}

void BobOmb::stomped()
{
    if (isReadyForRemoval() || state == STATE_IS_DYING) return;
	// Khi Bob-omb bị dẫm, nó sẽ được kích hoạt
    isActivated = true;
    velocity.x = 0;
}

void BobOmb::CollisionWithFireball(FireBall* fireball)
{
    if (isDying() || isDead()) return;
    Explode(); // Nổ ngay khi bị bắn
    fireball->setEntityDead();
    SmokeEffect* smokeright = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ 60, 120 });
    globalGameEngine->addEffect(smokeright);
    SmokeEffect* smokeleft = new SmokeEffect(Vector2{ getCenter().x, getTop() }, Vector2{ -60, 120 });
    globalGameEngine->addEffect(smokeleft);
}


void BobOmb::Explode() {
    if (state == STATE_IS_DYING) return;

    state = STATE_IS_DYING;
    deathTimer = BOBOMB_EXPLOSION_DURATION;
    velocity = { 0, 0 };
    RESOURCE_MANAGER.playSound("ENEMY_EXPLOSION"); // Cần thêm âm thanh này

    for (auto& p : globalGameEngine->getMultiplayers()) {
        if (p && p->getPhase() != CLEARLEVEL_PHASE && p->getPhase() != DEAD_PHASE) {
            float distance = Vector2Distance(position, p->getPosition());
            if (distance <= BOBOMB_EXPLOSION_RADIUS) {
                if (p->isImmortal() || p->isInvicible())
                    continue;
                else p->lostSuit();
            }
        }
    }
}

void BobOmb::loadEntity(const json& j)
{
    Enemy::loadEntity(j);
    isActivated = j["isActivated"];        
    fuseTimer = j["fuseTimer"];
}

void BobOmb::saveEntity(json& j) const
{
    Enemy::saveEntity(j);
    j["isActivated"] = isActivated;          
    j["fuseTimer"] = fuseTimer;

    // Add Tiled-compatible properties array
    j["properties"] = json::array({
        {
            { "name", "Name" },
            { "type", "string" },
            { "value", "Enemy" }
        },
        {
            { "name", "Type" },
            { "type", "string" },
            { "value", "BobOmb"}
        }
        });
}
