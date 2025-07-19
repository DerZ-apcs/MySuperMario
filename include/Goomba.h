#ifndef GOOMBA_H
#define GOOMBA_H
#include "../include/Enemy.h"
#include "../include/MediatorCollision.h"

class Goomba : public Enemy {
protected:
    float pauseTimer;
    bool isPaused;
    float detectMarioRange;
    MediatorCollision* mediatorCollision;
    float collisionTimer;
public:
    Goomba(Vector2 pos, Texture2D texture, MediatorCollision* mediator);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

class FlyingGoomba : public Goomba {
private:
    float jumpTimer; // Timer để kiểm soát tần suất nhảy
    float detectMarioRange;
	// MediatorCollision* mediatorCollision;
    float collisionTimer;
    bool hasWings;
public:
    FlyingGoomba(Vector2 pos, Texture2D texture, MediatorCollision* mediator);
    void Update() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif
