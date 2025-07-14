#ifndef BULLET_H
#define BULLET_H

#include "../include/Enemy.h"
#include "../include/EnemyFireBall.h"
#include "../include/Character.h"
#include <list>

class Bullet : public Enemy {
protected:
    static const int MAX_FIREBALLS = 10; 
public:
    Bullet(Vector2 pos, Texture2D texture, Direction direction);
	virtual ~Bullet();
    ENEMY_TYPE getEnemyType() const override;
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    virtual void ShootFireBall();
    float getScores() const override;
    void stomped() override;
};

class FireBullet : public Bullet {
private:
    float fireBallTimer; // Timer để bắn fireball
    static const float FIREBALL_INTERVAL; // Khoảng thời gian giữa các lần bắn
    static const float DETECTION_RANGE; // Phạm vi phát hiện Mario
public:
    FireBullet(Vector2 pos, Texture2D texture, Direction direction);
    void Update() override;
    void ShootFireBall() override;
};

#endif