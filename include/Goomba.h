#ifndef GOOMBA_H
#define GOOMBA_H
#include "../include/Enemy.h"

class Goomba : public Enemy {
public:
    Goomba(Vector2 pos, Texture2D texture);
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
public:
    FlyingGoomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif
