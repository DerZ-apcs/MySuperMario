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

inline Rectangle getProximityRect(Entity& entity, float radius);

class CollisionInfo {
public:
	virtual bool HandleCollision(Entity* entityA, Entity* entityB) = 0;
	virtual ~CollisionInfo() = default;
};
//  player vs block
class PlayerFloorInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class PlayerMovingBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class PlayerItemBlockInfo : public CollisionInfo { // ItemBlock = QuestionBlock, too lazy to change
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class PlayerBrickInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class PlayerBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// enemy vs block
class EnemyFloorInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class EnemyBrickInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class EnemyItemBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class EnemyBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// player vs enemy
class PlayerEnemyInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// player vs item
class PlayerItemInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
// item vs block
class ItemFloorInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class ItemBlockInfo: public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// player vs fireball
class FireBallPlayerInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// fireball vs enemy
class FireBallEnemyInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// fireball
class FireBallFloorInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class FireBallItemBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class FireBallBrickInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};
class FireBallBlockInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};

// enemy vs enemy
class EnemyEnemyInfo : public CollisionInfo {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB) override;
};



// select the corresponding Info
class CollisionInfoSelector {
public:
	static std::unique_ptr<CollisionInfo> getInfor(EntityType typeA, EntityType typeB, Blocks* block = nullptr);
};
// Interface
class CollisionInterface {
public:
	bool HandleCollision(Entity* entityA, Entity* entityB);
};
