// Spiny.h
#ifndef SPINY_H
#define SPINY_H

#include "../include/Enemy.h"       
#include "../include/Mario.h"
#include "../include/Tile.h"
#include "../include/FireBall.h"
#include "../include/Koopa.h"

class Spiny : public Enemy {
protected:
    static constexpr float SPINY_SPEED = 100.0f;
public:
    Spiny(Vector2 pos, Texture2D texture);

    void Update() override;
    void draw() override;
    void UpdateTexture() override;

    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void CollisionWithFireball(FireBall& fireball) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif // SPINY_H
