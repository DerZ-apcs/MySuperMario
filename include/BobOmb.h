#ifndef BOBOMB_H
#define BOBOMB_H
#include "../include/Enemy.h"

// Hằng số cho Bob-omb
const float BOBOMB_WALK_SPEED = 80.0f;
const float BOBOMB_FUSE_TIME = 3.0f;      // Thời gian đếm ngược trước khi nổ (giây)
const float BOBOMB_EXPLOSION_DURATION = 0.5f; // Thời gian hiệu ứng nổ tồn tại
const float BOBOMB_EXPLOSION_RADIUS = 100.0f;  // Bán kính ảnh hưởng của vụ nổ

class BobOmb : public Enemy {
private:
    bool isActivated;           // Cờ báo hiệu đã được kích hoạt (đốt ngòi)
    float fuseTimer;            // Bộ đếm thời gian trước khi nổ
public:
    BobOmb(Vector2 pos, Texture2D texture);
	float getScores() const override { return 100.0f; } // Điểm thưởng khi đánh bại Bob-omb
    virtual ~BobOmb();
    ENEMY_TYPE getEnemyType() const;
    void Update() override;
    void UpdateTexture() override;
    void stomped() override;
	void CollisionWithFireball(FireBall* fireball) override;
    void Explode(); // Hàm xử lý logic vụ nổ
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

#endif // BOBOMB_H