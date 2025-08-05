#ifndef GOOMBA_H
#define GOOMBA_H
#include "../include/Enemy.h"

class Goomba : public Enemy {
protected:
    float pauseTimer;
    bool isPaused;
    bool beattacked;
    float collisionTimer;
    float detectMarioRange;
public:
    bool isAttacked() const;
    ENEMY_TYPE getEnemyType() const;
    GOOMBA_TYPE getGoombaType() const;
    Goomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void attacked(Direction direction) override;
    float getScores() const override;
    void stomped() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

class FlyingGoomba : public Goomba {
private:
    float jumpTimer; // Timer để kiểm soát tần suất nhảy
    float detectMarioRange;
    float collisionTimer;
    bool hasWings;
    bool isSearchPaused;
	float searchCooldownTimer;
public:
    ENEMY_TYPE getEnemyType() const;
    GOOMBA_TYPE getGoombaType() const;
    FlyingGoomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
    float getScores() const override;
    void setJumpTimer(float time);
    void stomped() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

#endif
