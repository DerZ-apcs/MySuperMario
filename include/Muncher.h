#ifndef MUNCHER_H
#define MUNCHER_H

#include "../include/Enemy.h"
#include "../include/ResourceManager.h"

class Muncher : public Enemy {
private:
    const float animationSpeed = 0.25f; 

public:
    Muncher(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithFireball(FireBall& fireball) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif 