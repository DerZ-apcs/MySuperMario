#ifndef GOOMBA_H
#define GOOMBA_H
#include "../include/Enemy.h"

class Goomba : public Enemy {
private:
    float pauseTimer;
    bool isPaused;
    float detectMarioRange;
    bool beattacked;
public:
    bool isAttacked() const;
    ENEMY_TYPE getEnemyType() const;
    Goomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void attacked(Direction direction) override;
    float getScores() const override;
    void stomped() override;
};

class FlyingGoomba : public Goomba {
private:
    float jumpTimer; // Timer để kiểm soát tần suất nhảy
    float detectMarioRange;
    float collisionTimer;
public:
    ENEMY_TYPE getEnemyType() const;
    FlyingGoomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
    float getScores() const override;

};

#endif
