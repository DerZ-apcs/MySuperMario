#ifndef KOOPA_H
#define KOOPA_H
#include "../include/Enemy.h"

class Koopa : public Enemy {
protected:
    float reviveTimer;
    bool isReviving; 
    float reviveShakeTimer;
public:
    Koopa(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void CollisionWithFireball(FireBall& fireball) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

class YellowKoopa : public Koopa {
public:
    YellowKoopa(Vector2 pos, Texture2D texture);
    void UpdateTexture() override;
};

class BlueKoopa : public Koopa {
public:
    BlueKoopa(Vector2 pos, Texture2D texture);
    void UpdateTexture() override;
};
#endif