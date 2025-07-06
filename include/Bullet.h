#ifndef BULLET_H
#define BULLET_H

#include "../include/Enemy.h"
#include "../include/EnemyFireBall.h"
#include "../include/Mario.h"
#include <list>

class Bullet : public Enemy {
protected:
    static const int MAX_FIREBALLS = 10; 
    std::list<EnemyFireBall*> fireballs; 
public:
    Bullet(Vector2 pos, Texture2D texture, Direction direction);
	virtual ~Bullet();
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
    virtual void ShootFireBall();
	std::list<EnemyFireBall*>* getFireBalls() { return &fireballs; }
};

class FireBullet : public Bullet {
private:
    float fireBallTimer; // Timer để bắn fireball
    static const float FIREBALL_INTERVAL; // Khoảng thời gian giữa các lần bắn
    static const float DETECTION_RANGE; // Phạm vi phát hiện Mario
    Mario& mario; // Tham chiếu đến Mario
public:
    FireBullet(Vector2 pos, Texture2D texture, Direction direction, Mario& mario);
    void Update() override;
    void ShootFireBall() override;
};

#endif