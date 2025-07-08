#include "../include/CollisionInfo.h"
#include "../include/Character.h"
#include "../include/Blocks.h"
#include "../include/Floor.h"
#include "../include/MovingBlock.h"
#include "../include/Brick.h"
#include "../include/TemporaryBlock.h"
#include "../include/HiddenBlock.h"
#include "../include/SolidBlock.h"
#include "../include/DecorBlock.h"
#include "../include/Shell.h"
#include "../include/ItemBlock.h"
#include <iostream>

inline Rectangle getProximityRect(Entity& entity, float radius)
{
	Rectangle rect = entity.getRect();
	return Rectangle{
		rect.x - radius,
		rect.y - radius,
		rect.width + radius * 2,
		rect.height + radius * 2
	};
}

static bool shouldCheckCollision(Entity* entityA, Entity* entityB, float proximityRadius = 10.f)
{
	if (!entityA || !entityB) return false;

	// Calculate proximity bounds for entityA directly
	Rectangle ProximityA = getProximityRect(*entityA, proximityRadius);
	return CheckCollisionRecs(ProximityA, entityB->getRect());
}


bool PlayerFloorInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Floor* floor = dynamic_cast<Floor*>(entityB);

	if (!character || !floor || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*floor);

	if (Colltype != COLLISION_TYPE_SOUTH)
		return false;
	character->setPosition(Vector2{ character->getX(), floor->getY() - character->getHeight() });
	character->setState(ON_GROUND);
	character->setVelY(0);
	return true;
}

bool PlayerMovingBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	MovingBlock* block = dynamic_cast<MovingBlock*>(entityB);
	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_NONE)
		return false;
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
	return true;
}

bool PlayerItemBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	ItemBlock* block = dynamic_cast<ItemBlock*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
		character->setVelY(0);
		block->releaseItem(character); // set release
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

bool PlayerBrickInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Brick* block = dynamic_cast<Brick*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
		character->setVelY(0);
		block->breakBrick();
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
	return true;
}

bool PlayerBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Blocks* block = dynamic_cast<Blocks*>(entityB);
	
	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_NONE)
		return false;
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
	return true;
}

// enemy
bool EnemyFloorInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	Floor* floor = dynamic_cast<Floor*>(entityB);

	if (!enemy || !floor || !enemy->getCollisionAvailable())
		return false;
	if (enemy->getEnemyType() == PIRANHA) return false;

	CollisionType Colltype = enemy->CheckCollision(*floor);

	if (Colltype != COLLISION_TYPE_SOUTH)
		return false;
	enemy->setPosition(Vector2{ enemy->getX(), enemy->getY() - enemy->getHeight() });
	enemy->setState(ON_GROUND);
	enemy->setVelY(0);
	return true;
}
bool EnemyBrickInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	Brick* block = dynamic_cast<Brick*>(entityB);

	if (!enemy || !block || !enemy->getCollisionAvailable())
		return false;
	if (enemy->getEnemyType() == PIRANHA) return false;

	CollisionType Colltype = enemy->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE) return false;
	if (enemy->getVelX() != 0 || enemy->getEnemyType() == SHELL) {
		
		switch (Colltype) {
		case COLLISION_TYPE_NORTH:
			enemy->setPosition(Vector2{ enemy->getX(), block->getY() + block->getHeight() });
			enemy->setVelY(0);
			//state = FALLING;
			break;
		case COLLISION_TYPE_SOUTH:
			enemy->setPosition(Vector2{ enemy->getX(), block->getY() - enemy->getHeight() });
			enemy->setState(ON_GROUND);
			enemy->setVelY(0);
			break;
		case COLLISION_TYPE_EAST:
			enemy->setPosition(Vector2{ block->getX() - enemy->getWidth(), enemy->getY() });
			enemy->setVelX(enemy->getVelX() * -1);
			enemy->setDirection(LEFT);
			break;
		case COLLISION_TYPE_WEST:
			enemy->setPosition(Vector2{ block->getX() + block->getWidth(), enemy->getY() });
			enemy->setVelX(enemy->getVelX() * -1);
			enemy->setDirection(RIGHT);
			break;
		default:
			break;
		}

		if (Shell* shell = dynamic_cast<Shell*>(enemy)) {
			if (!shell->getIsHold()) {
				block->breakBrick();
			}
		}
	}
	return true;
}

bool EnemyItemBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	ItemBlock* block = dynamic_cast<ItemBlock*>(entityB);

	if (!enemy || !block || !enemy->getCollisionAvailable())
		return false;
	if (enemy->getEnemyType() == PIRANHA) return false;

	CollisionType Colltype = enemy->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE) 
		return false;
	if (enemy->getVelX() != 0 || enemy->getEnemyType() == SHELL) {

		switch (Colltype) {
		case COLLISION_TYPE_NORTH:
			enemy->setPosition(Vector2{ enemy->getX(), block->getY() + block->getHeight() });
			enemy->setVelY(0);
			//state = FALLING;
			break;
		case COLLISION_TYPE_SOUTH:
			enemy->setPosition(Vector2{ enemy->getX(), block->getY() - enemy->getHeight() });
			enemy->setState(ON_GROUND);
			enemy->setVelY(0);
			break;
		case COLLISION_TYPE_EAST:
			enemy->setPosition(Vector2{ block->getX() - enemy->getWidth(), enemy->getY() });
			enemy->setVelX(enemy->getVelX() * -1);
			enemy->setDirection(LEFT);
			break;
		case COLLISION_TYPE_WEST:
			enemy->setPosition(Vector2{ block->getX() + block->getWidth(), enemy->getY() });
			enemy->setVelX(enemy->getVelX() * -1);
			enemy->setDirection(RIGHT);
			break;
		default:
			break;
		}

		if (Shell* shell = dynamic_cast<Shell*>(enemy)) {
			if (!shell->getIsHold()) {
				block->releaseItem(enemy);
			}
		}
	}
	return true;
}
bool EnemyBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	Blocks* block = dynamic_cast<Blocks*>(entityB);

	if (!enemy || !block || !enemy->getCollisionAvailable())
		return false;
	CollisionType Colltype = enemy->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		enemy->setPosition(Vector2{ enemy->getX(), block->getY() + block->getHeight() });
		enemy->setVelY(0);
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		enemy->setPosition(Vector2{ enemy->getX(), block->getY() - enemy->getHeight() });
		enemy->setState(ON_GROUND);
		enemy->setVelY(0);
		break;
	case COLLISION_TYPE_EAST:
		enemy->setPosition(Vector2{ block->getX() - enemy->getWidth(), enemy->getY() });
		enemy->setVelX(enemy->getVelX() * -1);
		enemy->setDirection(LEFT);

		break;
	case COLLISION_TYPE_WEST:
		enemy->setPosition(Vector2{ block->getX() + block->getWidth(), enemy->getY() });
		enemy->setVelX(enemy->getVelX() * -1);
		enemy->setDirection(RIGHT);
		break;
	default:
		break;
	}
	return true;
}

// fireball
bool FireBallFloorInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Floor* floor = dynamic_cast<Floor*>(entityB);

	if (!fireball || !floor || !fireball->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*floor);

	if (Colltype != COLLISION_TYPE_SOUTH)
		return false;
	fireball->setPosition(Vector2{ fireball->getX(), fireball->getY() - fireball->getHeight() });
	fireball->setVelY(fireball->getVelY() * -1);
	return true;
}

bool FireBallItemBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	ItemBlock* block = dynamic_cast<ItemBlock*>(entityB);

	if (!fireball || !block || !fireball->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;

	fireball->setEntityDead();
	fireball->setCollisionAvailable(false);
	RESOURCE_MANAGER.playSound("bump.wav");
	//Effect* smoke = new Effect();
	block->releaseItem(fireball);
	return true;
}

bool FireBallBrickInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Brick* block = dynamic_cast<Brick*>(entityB);

	if (!fireball || !block || !fireball->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	
	fireball->setEntityDead();
	fireball->setCollisionAvailable(false);
	RESOURCE_MANAGER.playSound("bump.wav");
	//Effect* smoke = new Effect();
	block->breakBrick();
	return true;
}

bool FireBallBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Blocks* block = dynamic_cast<Blocks*>(entityB);

	if (!fireball || !block || !fireball->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype)
	{
	case COLLISION_TYPE_NORTH:
		fireball->setPosition(Vector2{ fireball->getX(), block->getY() + block->getHeight() });
		fireball->setVelY(0);
		break;
	case COLLISION_TYPE_SOUTH:
		fireball->setPosition(Vector2{ fireball->getX(), block->getY() - fireball->getHeight() });
		fireball->setVelY(fireball->getVelY() * -1);
		break;
	case COLLISION_TYPE_EAST:
		fireball->setPosition(Vector2{ block->getX() - fireball->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -1);
		break;
	case COLLISION_TYPE_WEST:
		fireball->setPosition(Vector2{ block->getX() + block->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -1);
		break;
	default:
		break;
	}
	return true;
}

bool PlayerEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	return true;
}

bool PlayerItemInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Item* item = dynamic_cast<Item*>(entityB);

	if (!character || !item || !character->getCollisionAvailable() || !item->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*item);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	character->collisionWithItem(item);
	item->setEntityDead();
	return true;
}

bool ItemFloorInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Item* item = dynamic_cast<Item*>(entityA);
	Floor* floor = dynamic_cast<Floor*>(entityB);

	if (!item || !floor || !item->getCollisionAvailable())
		return false;
	CollisionType Colltype = item->CheckCollision(*floor);

	if (Colltype != COLLISION_TYPE_SOUTH)
		return false;
	item->setPosition(Vector2{ item->getX(), item->getY() - item->getHeight() });
	item->setState(ON_GROUND);
	item->setVelY(0);
	return true;
}

bool ItemBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Item* item = dynamic_cast<Item*>(entityA);
	Blocks* block = dynamic_cast<Blocks*>(entityB);

	if (!item || !block || item->getCollisionAvailable() == false)
		return false;
	CollisionType Colltype = item->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		item->setPosition(Vector2{ item->getX(), block->getY() + block->getHeight() });
		item->setVelY(0);
		break;
	case COLLISION_TYPE_SOUTH:
		item->setPosition(Vector2{ item->getX(), block->getY() - item->getHeight() });
		item->setState(ON_GROUND);
		item->setVelY(0);
		break;
	case COLLISION_TYPE_EAST:
		item->setPosition(Vector2{ block->getX() - item->getWidth(), item->getY() });
		item->setVelX(item->getVelX() * -1);
		item->setDirection(LEFT);
		break;
	case COLLISION_TYPE_WEST:
		item->setPosition(Vector2{ block->getX() + block->getWidth(), item->getY() });
		item->setVelX(item->getVelX() * -1);
		item->setDirection(RIGHT);
		break;
	default:
		break;
	}
	return true;
}

bool FireBallPlayerInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Character* character = dynamic_cast<Character*>(entityB);

	if (!fireball || !character || !fireball->getCollisionAvailable() || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*character);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;

	character->CollisionWithFireball(fireball);
	return true;
}

bool FireBallEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Enemy* enemy = dynamic_cast<Enemy*>(entityB);
	if (!fireball || !enemy || !fireball->getCollisionAvailable() || !enemy->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*enemy);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	enemy->CollisionWithFireBall(fireball);
	return true;
}

bool EnemyEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy1 = dynamic_cast<Enemy*>(entityA);
	Enemy* enemy2 = dynamic_cast<Enemy*>(entityB);

	if (!enemy1 || !enemy2 || enemy1->getCollisionAvailable() == false || enemy2->getCollisionAvailable() == false)
		return false;
	if (enemy1->getEnemyType() != SHELL)
		return false;
	CollisionType Colltype = enemy1->CheckCollision(*enemy2);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	enemy2->attacked(enemy1->getDir()); // enemy1 (shell) attack enemy2
	if (enemy2->getEnemyType() == SHELL)
		enemy1->attacked(enemy2->getDir());
	return true;
}


std::unique_ptr<CollisionInfo> CollisionInfoSelector::getInfor(EntityType typeA, EntityType typeB, Blocks* block)
{
	if (typeA == CHARACTER && typeB == BLOCK) {
		if (block && block->getBlockType() == FLOOR)
			return std::make_unique<PlayerFloorInfo>();
		if (block && block->getBlockType() == MOVINGBLOCK)
			return std::make_unique<PlayerMovingBlockInfo>();
		if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<PlayerItemBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<PlayerBrickInfo>();
		return std::make_unique<PlayerBlockInfo>();
	}
	if (typeA == ENEMY && typeB == BLOCK)
	{
		if (block && block->getBlockType() == FLOOR)
			return std::make_unique<PlayerFloorInfo>();
		if (block && block->getBlockType() == SOLIDBLOCK)
			return make_unique<EnemyBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<EnemyBrickInfo>();
		if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<EnemyItemBlockInfo>();
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
		return std::make_unique<FireBallPlayerInfo>();
	}
	if (typeA == FIREBALL && typeB == ENEMY) {
		return std::make_unique<FireBallEnemyInfo>();
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


bool CollisionIterface::HandleCollision(Entity* entityA, Entity* entityB)
{
	if (!shouldCheckCollision(entityA, entityB)) {
		return false;
	}
	auto typeA = entityA->getEntityType();
	auto typeB = entityB->getEntityType();

	Blocks* block = dynamic_cast<Blocks*>(entityB);
	auto Infor = CollisionInfoSelector::getInfor(typeA, typeB, block);
	if (!Infor) {
		Infor = CollisionInfoSelector::getInfor(typeB, typeA, dynamic_cast<Blocks*>(entityA));
	}
	if (Infor) {
		return Infor->HandleCollision(entityA, entityB);
	}
	else {
		std::cout << "No collision strategy found for entities: "
			<< static_cast<int>(typeA) << " and " << static_cast<int>(typeB) << std::endl;
	}
	return false;
}


