#ifndef BOBOMB_H
#define BOBOMB_H

#include "../include/Enemy.h"
#include "../include/MediatorCollision.h"

// Hằng số cho Bob-omb
const float BOBOMB_WALK_SPEED = 80.0f;
const float BOBOMB_FUSE_TIME = 3.0f;      // Thời gian đếm ngược trước khi nổ (giây)
const float BOBOMB_EXPLOSION_DURATION = 0.5f; // Thời gian hiệu ứng nổ tồn tại
const float BOBOMB_EXPLOSION_RADIUS = 80.0f;  // Bán kính ảnh hưởng của vụ nổ

class BobOmb : public Enemy {
private:
    bool isActivated;           // Cờ báo hiệu đã được kích hoạt (đốt ngòi)
    float fuseTimer;            // Bộ đếm thời gian trước khi nổ
    MediatorCollision* mediatorCollision; // Để kiểm tra va chạm với Mario khi nổ

public:
    BobOmb(Vector2 pos, Texture2D texture, MediatorCollision* mediator);
    virtual ~BobOmb();

    void Update() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithFireball(FireBall& fireball) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;

private:
    void Explode(); // Hàm xử lý logic vụ nổ
};

#endif // BOBOMB_H