#ifndef MEDIATORCOLLISION_H
#define MEDIATORCOLLISION_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include "../include/Tile.h"
#include "../include/FireBall.h"
#include "../include/Enemy.h"

class MediatorCollision {
private:
    void HandlePlayerWithTiles(Mario*& mario, Tile*& tile, CollisionType Colltype);
    void HandleFireballWithTiles(FireBall*& fireball, Tile*& tile, CollisionType Colltype);
    void HandleEnemyWithMario(Enemy*& enemy, Mario*& mario, CollisionType Colltype);
public:
    void HandleCollision(Entity* entity1, Entity* entity2);
};
#endif