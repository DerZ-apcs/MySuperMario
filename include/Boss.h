#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "CollisionInfo.h"
#include <vector>

class Boss : public Enemy {
protected:
    int maxHp;
    int currentHp;
    bool vulnerable;
    float stateTimer;

public:
    Boss(Vector2 pos, Vector2 size, Texture2D initialTexture, int hp);
    virtual ~Boss() = default;
    virtual void takeDamage(int amount);
    virtual void die();

    virtual void onDeath();

    virtual void onHit();

    void Update() override;

    virtual void updateBehavior() = 0;

    virtual void applyPhysics();

    ENEMY_TYPE getEnemyType() const override {
		return ENEMY_TYPE::BOSS;
    }
};

#endif