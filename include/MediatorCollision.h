#ifndef MEDIATORCOLLISION_H
#define MEDIATORCOLLISION_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include "../include/Tile.h"
#include "../include/FireBall.h"
#include "../include/Enemy.h"
#include "../include/EnemyFireBall.h"

class MediatorCollision {
private:
    void HandlePlayerWithTiles(Mario*& mario, Tile*& tile, CollisionType Colltype);
    void HandleFireballWithTiles(FireBall*& fireball, Tile*& tile, CollisionType Colltype);
    void HandleEnemyFireballWithTiles(EnemyFireBall*& fireball, Tile*& tile, CollisionType Colltype);
    void HandleEnemyWithMario(Enemy*& enemy, Mario*& mario, CollisionType Colltype);
    void HandleFireballWithEnemy(FireBall*& fireball, Enemy*& enemy, CollisionType collType);
    void HandleEnemyFireballWithMario(EnemyFireBall*& fireball, Mario*& mario, CollisionType collType);
    Mario* mario;
public:
    void SetMario(Mario* m);
    Mario* GetMario() const;
    void HandleCollision(Entity* entity1, Entity* entity2);
};

#endif