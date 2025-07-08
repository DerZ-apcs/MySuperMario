#ifndef MEDIATORCOLLISION_H
#define MEDIATORCOLLISION_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include "../include/Tile.h"
#include "../include/Brick.h"
#include "../include/QuestionBlock.h"
#include "../include/Coin.h"
class MediatorCollision {
private:
	void HandlePlayerWithTiles(Mario*& mario, Tile*& tile, CollisionType Colltype);
	void HandlePlayerWithBrick(Mario*& mario, Brick*& brick, CollisionType Colltype);
	void HandleFireballWithTIles(FireBall*& fireball, Tile*& tile, CollisionType Colltype);
	void HandlePowerItemWithTiles(PowerItem*& item, Tile*& tile, CollisionType Colltype);
	void HandlePlayerWithCoins(Mario*& mario, Coin*& coin, CollisionType Colltype);
	void HandlePlayerWithPowerItem(Mario*& mario, PowerItem*& item, CollisionType Colltype);

public:
	void HandleCollision(Entity* entity1, Entity* entity2);
};
#endif