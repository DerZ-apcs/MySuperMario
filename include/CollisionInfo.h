#pragma once
#include "../include/Entity.h"
//#include "../include/Character.h"
#include "../include/Tile.h"
#include "../include/FireBall.h"
#include "../include/Enemy.h"
#include "../include/Item.h"
#include "../include/Collision.h"

class Blocks;
class Character;
class FireBall;
class Tile;
class Enemy;

class CollisionInfo {
public:
	virtual void HandleCollision(Entity* entityA, Entity* entityB) = 0;
	virtual ~CollisionInfo() = default;
};

class PlayerBlockInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class EnemyBlockInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};
class PlayerEnemyInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class PlayerItemInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class ItemBlockInfo: public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class PlayerFireBallInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class EnemyFireBallInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class FireBallBlockInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};

class EnemyEnemyInfo : public CollisionInfo {
public:
	void HandleCollision(Entity* entityA, Entity* entityB) override;
};


class CollisionInfoSelector {
public:
	static std::unique_ptr<CollisionInfo> getInfor(EntityType typeA, EntityType typeB, Blocks* block = nullptr);
};

class CollisionIterface {
public:
	void HandleCollision(Entity* entityA, Entity* entityB);
};
