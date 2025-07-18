#ifndef REX_H
#define REX_H
#include "../include/Enemy.h"
#include "../include/MediatorCollision.h"

enum RexState {
    REX_NORMAL,
    REX_COMPRESSED
};

class Rex : public Enemy {
private:
    RexState rexState;
public:
    Rex(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void CollisionWithFireball(FireBall& fireball) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
   /* void updateCollision() override;*/
};

#endif