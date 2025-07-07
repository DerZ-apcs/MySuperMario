#include "../include/CollisionInfo.h"
#include "../include/Character.h"
#include "../include/Blocks.h"
#include <iostream>


void PlayerBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Tile* block = dynamic_cast<Tile*>(entityB);
	
	if (!character || !block || !character->getCollisionAvailable())
		return;
	CollisionType Colltype = character->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
		character->setVelY(0);
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		character->setPosition(Vector2{ character->getX(), block->getY() - character->getHeight() });
		character->setState(ON_GROUND);
		character->setVelY(0);
		break;
	case COLLISION_TYPE_EAST:
		character->setPosition(Vector2{ block->getX() - character->getWidth(), character->getY() });
		character->setVelX(0);
		break;
	case COLLISION_TYPE_WEST:
		character->setPosition(Vector2{ block->getX() + block->getWidth(), character->getY() });
		character->setVelX(0);
		break;
	default:
		break;
	}
}

void EnemyBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{

}

void FireBallBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Tile* tile = dynamic_cast<Tile*>(entityB);

	if (!fireball || !tile || !fireball->getCollisionAvailable())
		return;
	CollisionType Colltype = fireball->CheckCollision(*tile);
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype)
	{
	case COLLISION_TYPE_NORTH:
		fireball->setPosition(Vector2{ fireball->getX(), tile->getY() + tile->getHeight() });
		fireball->setVelY(0);
		break;
	case COLLISION_TYPE_SOUTH:
		fireball->setPosition(Vector2{ fireball->getX(), tile->getY() - fireball->getHeight() });
		fireball->setVelY(fireball->getVelY() * -1);
		break;
	case COLLISION_TYPE_EAST:
		fireball->setPosition(Vector2{ tile->getX() - fireball->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -1);
		break;
	case COLLISION_TYPE_WEST:
		fireball->setPosition(Vector2{ tile->getX() + tile->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -1);
		break;
	default:
		break;
	}
}

void PlayerEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}
void PlayerItemInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}
void ItemBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}
void PlayerFireBallInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}
void EnemyFireBallInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}
void EnemyEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
}


std::unique_ptr<CollisionInfo> CollisionInfoSelector::getInfor(EntityType typeA, EntityType typeB, Blocks* block)
{
	if (typeA == CHARACTER && typeB == BLOCK) {
		/*if (block && block->getBlockType() == MOVINGBLOCK)
			return std::make_unique<PlayerMovingBlockInfo>();
		if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<PlayerItemBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<PlayerBrickInfo>();*/
		return std::make_unique<PlayerBlockInfo>();
	}
	if (typeA == ENEMY && typeB == BLOCK)
	{
		/*if (block && block->getBlockType() == SOLIDBLOCK)
			return make_unique<EnemyBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<EnemyBrickInfo>();
		if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<EnemyItemBlockInfo>();*/
		return  make_unique<EnemyBlockInfo>();
	}
	if (typeA == CHARACTER && typeB == ENEMY)
	{
		return  make_unique<PlayerEnemyInfo>();
	}
	if (typeA == CHARACTER && typeB == ITEM)
	{
		return std::make_unique<PlayerItemInfo>();
	}
	if (typeA == ITEM && typeB == BLOCK)
	{
		return std::make_unique<ItemBlockInfo>();
	}

	if (typeA == FIREBALL && typeB == CHARACTER) {
		return std::make_unique<PlayerFireBallInfo>();
	}
	if (typeA == FIREBALL && typeB == ENEMY) {
		return std::make_unique<EnemyFireBallInfo>();
	}
	if (typeA == FIREBALL && typeB == BLOCK) {
		/*if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<FireBallItemBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<FireBallBrickInfo>();*/

		return std::make_unique<FireBallBlockInfo>();
	}
	if (typeA == ENEMY && typeB == ENEMY) {
		return std::make_unique<EnemyEnemyInfo>();
	}


	return nullptr;
}


void CollisionIterface::HandleCollision(Entity* entityA, Entity* entityB)
{
	if (entityA->CheckCollision(*entityB) == COLLISION_TYPE_NONE) {
		return;
	}
	auto typeA = entityA->getEntityType();
	auto typeB = entityB->getEntityType();

	Blocks* block = dynamic_cast<Blocks*>(entityB);
	auto Infor = CollisionInfoSelector::getInfor(typeA, typeB, block);
	if (!Infor) {
		Infor = CollisionInfoSelector::getInfor(typeB, typeA, dynamic_cast<Blocks*>(entityA));
	}
	if (Infor) {
		Infor->HandleCollision(entityA, entityB);
	}
	else {
		std::cout << "No collision strategy found for entities: "
			<< static_cast<int>(typeA) << " and " << static_cast<int>(typeB) << std::endl;
	}
}