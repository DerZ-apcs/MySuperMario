#ifndef BULLET_H
#define BULLET_H

#include "../include/Enemy.h"

class Bullet : public Enemy {
public:
    Bullet(Vector2 pos, Texture2D texture, Direction direction);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif