#include "../include/CollisionInfo.h"
#include "../include/Character.h"
#include "../include/Blocks.h"
#include "../include/Floor.h"
#include "../include/MovingBlock.h"
#include "../include/Brick.h"
#include "../include/TemporaryBlock.h"
#include "../include/RotatingBlock.h"
#include "../include/HiddenBlock.h"
#include "../include/SolidBlock.h"
#include "../include/CloudBlock.h"
#include "../include/NoteBlock.h"
#include "../include/DecorBlock.h"
#include "../include/Shell.h"
#include "../include/SmokeEffect.h"
#include "../include/ItemBlock.h"
#include "../include/CoinBlock.h"
#include "../include/Coin.h"
#include "../include/PowerItem.h"
#include "../include/PiranhaPlant.h"
#include <iostream>
#include <GameEngine.h>
#include <BobOmb.h>

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

static bool shouldCheckCollision(Entity* entityA, Entity* entityB, float proximityRadius = 5.f)
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
	if (character->getVelocity().y > 0) {
		character->setState(ON_GROUND);
		character->setVelY(0);
		character->setPosition(Vector2{ character->getX(), floor->getY() - character->getHeight() });
	}
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
		if (block->getActive())
			block->Activate();
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

bool PlayerCloudBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	CloudBlock* block = dynamic_cast<CloudBlock*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_SOUTH && character->getVelY() > 0) {
		if (character->getState() != SINKING) {
			character->setPosition(Vector2{ character->getX(), block->getY() - character->getHeight() });
			character->setVelY(0);
			character->setState(SINKING);
		}

		character->setSinkingTime(0.05f); // refresh timer 
		return true;
	}

	return false;
}

bool PLayerNoteBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	NoteBlock* block = dynamic_cast<NoteBlock*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
		character->setVelY(0);
		block->setBounceDir(BOUNCE_UP);
		break;
	case COLLISION_TYPE_SOUTH:
		character->setPosition(Vector2{ character->getX(), block->getY() - character->getHeight() });
		character->setState(JUMPING);
		if (character->getVelY() > 35) {
			character->setVelY(max(character->getVelY() * -1.5f, -1550.0f)); // bounce effect
			block->setBounceDir(BOUNCE_DOWN);
		}
		else { character->setVelY(0); }
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

bool PlayerCoinBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	CoinBlock* block = dynamic_cast<CoinBlock*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
		character->setVelY(50);
		if (block->getActive()) {
			block->Activate();
			character->setCoins(character->getCoins() + 1);
			Coin coin;
			character->setScores(character->getScores() + coin.getPoint());
		}
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
// enemy
bool EnemyFloorInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	Floor* floor = dynamic_cast<Floor*>(entityB);

	if (!enemy || !floor || !enemy->getCollisionAvailable())
		return false;
	if (enemy->getEnemyType() == PIRANHA) {
		if (dynamic_cast<PiranhaPlant*>(enemy)->getPiranhaType() != JUMPING_PIRANHA)
			return false; // only jumping piranha can collide with blocks
	}
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
	if (enemy->getEnemyType() == PIRANHA) {
		if (dynamic_cast<PiranhaPlant*>(enemy)->getPiranhaType() != JUMPING_PIRANHA)
			return false; // only jumping piranha can collide with blocks
	}
	CollisionType Colltype = enemy->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE) 
		return false;
	if (enemy->getEnemyType() == BULLET) {
		enemy->setVel({ 0, 0 });
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
		enemy->setEntityDead();
		return true;
	}
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

		if (enemy->getEnemyType() == SHELL) {
			if (enemy->getIsKicked())
				block->breakBrick();
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
	if (enemy->getEnemyType() == PIRANHA) {
		if (dynamic_cast<PiranhaPlant*>(enemy)->getPiranhaType() != JUMPING_PIRANHA)
			return false; // only jumping piranha can collide with blocks
	}
	CollisionType Colltype = enemy->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE) 
		return false;

	if (enemy->getEnemyType() == BULLET) {
		enemy->setVel({ 0, 0 });
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomp.wav");
		enemy->setEntityDead();
		return true;
	}
	if (enemy->getVelX() != 0 || enemy->getVelY() != 0 || enemy->getEnemyType() == SHELL) {

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

		if (enemy->getEnemyType() == SHELL) {
			if (enemy->getIsKicked() && block->getActive())
				//block->releaseItem(enemy);
				block->Activate();
		}
	}
	return true;
}
bool EnemyBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy = dynamic_cast<Enemy*>(entityA);
	Blocks* block = dynamic_cast<Blocks*>(entityB);

	if (!enemy || !block || !enemy->getCollisionAvailable() || !block->getCollisionAvailable() || enemy->getEnemyType() == PIRANHA)
		return false;
	CollisionType Colltype = enemy->CheckCollision(*block);

	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	if (enemy->getEnemyType() == BULLET) {
		return false;
	}
	if (enemy->getEnemyType() == PIRANHA) {
		if (dynamic_cast<PiranhaPlant*>(enemy)->getPiranhaType() != JUMPING_PIRANHA)
			return false; // only jumping piranha can collide with blocks
	}
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		enemy->setPosition(Vector2{ enemy->getX(), block->getY() + block->getHeight() });
		enemy->setVelY(0);

		break;
	case COLLISION_TYPE_SOUTH:
		enemy->setPosition(Vector2{ enemy->getX(), block->getY() - enemy->getHeight() });
		enemy->setState(ON_GROUND);
		enemy->setVelY(0);
		if (enemy->getEnemyType() == GOOMBA && dynamic_cast<Goomba*>(enemy)->getGoombaType() == FLYING_GOOMBA) {
			dynamic_cast<FlyingGoomba*>(enemy)->setJumpTimer(0.5f);
		}
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
	if (Colltype == COLLISION_TYPE_EAST || Colltype == COLLISION_TYPE_WEST) {
		if (enemy->getEnemyType() == REX || enemy->getEnemyType() == GOOMBA)
			enemy->setCollisionTimer(0.5f); // vo hieu hoa duoi character 0.5s
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
	fireball->setVelY(fireball->getVelY() * -0.9f);
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

	if (block->getActive()) {
		block->Activate();
		fireball->setEntityDead();
		fireball->setCollisionAvailable(false);
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("bump.wav");
		SmokeEffect* smoke = new SmokeEffect(Vector2{ block->getCenter().x, block->getTop() }, Vector2{ 0, -200 });
		globalGameEngine->addEffect(smoke);
	}
	switch (Colltype)
	{
	case COLLISION_TYPE_NORTH:
		fireball->setPosition(Vector2{ fireball->getX(), block->getY() + block->getHeight() });
		fireball->setVelY(0);
		break;
	case COLLISION_TYPE_SOUTH:
		fireball->setPosition(Vector2{ fireball->getX(), block->getY() - fireball->getHeight() });
		fireball->setVelY(fireball->getVelY() * -0.9f);
		break;
	case COLLISION_TYPE_EAST:
		fireball->setPosition(Vector2{ block->getX() - fireball->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	case COLLISION_TYPE_WEST:
		fireball->setPosition(Vector2{ block->getX() + block->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	default:
		break;
	}
	
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
	
	block->breakBrick();
	fireball->setEntityDead();
	fireball->setCollisionAvailable(false);
	if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("bump.wav");
	SmokeEffect* smoke = new SmokeEffect(Vector2{ block->getCenter().x, block->getTop() }, Vector2{ 0, -200 });
	globalGameEngine->addEffect(smoke);
	
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
		fireball->setVelY(fireball->getVelY() * -0.9f);
		break;
	case COLLISION_TYPE_EAST:
		fireball->setPosition(Vector2{ block->getX() - fireball->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	case COLLISION_TYPE_WEST:
		fireball->setPosition(Vector2{ block->getX() + block->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	default:
		break;
	}
	return true;
}

bool PlayerEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	Enemy* enemy = dynamic_cast<Enemy*>(entityB);

	if (!character || !enemy || !character->getCollisionAvailable() || !enemy->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*enemy);

	if (Colltype == COLLISION_TYPE_NONE) return false;

	character->collisionWithEnemy(enemy, Colltype);

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
	PowerItem* powerItem = dynamic_cast<PowerItem*>(item);

	if (!item || !block || !item->getCollisionAvailable())
		return false;
	if (powerItem && powerItem->getPowerUpState() != ACTIVE) {
		return false;
	}
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
// enemy fireball
bool FireBallPlayerInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	EnemyFireBall* fireball = dynamic_cast<EnemyFireBall*>(entityA);
	Character* character = dynamic_cast<Character*>(entityB);

	if (!fireball || !character || !fireball->getCollisionAvailable() || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = fireball->CheckCollision(*character);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;

	character->CollisionWithFireball(fireball);
	return true;
}

bool EnemyFireBallBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	EnemyFireBall* fireball = dynamic_cast<EnemyFireBall*>(entityA);
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
		fireball->setVelY(fireball->getVelY() * -0.9f);
		break;
	case COLLISION_TYPE_SOUTH:
		fireball->setPosition(Vector2{ fireball->getX(), block->getY() - fireball->getHeight() });
		fireball->setVelY(fireball->getVelY() * -0.9f);
		break;
	case COLLISION_TYPE_EAST:
		fireball->setPosition(Vector2{ block->getX() - fireball->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	case COLLISION_TYPE_WEST:
		fireball->setPosition(Vector2{ block->getX() + block->getWidth(), fireball->getY() });
		fireball->setVelX(fireball->getVelX() * -0.9f);
		break;
	default:
		break;
	}
	return true;
}

// character fireball
bool FireBallEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	FireBall* fireball = dynamic_cast<FireBall*>(entityA);
	Enemy* enemy = dynamic_cast<Enemy*>(entityB);
	if (!fireball || !enemy || !fireball->getCollisionAvailable() || !enemy->getCollisionAvailable())
		return false;
	if (enemy->getEnemyType() == MUNCHER)
		return false;
	if (enemy->getEnemyType() == BOBOMB) {
		if (enemy->isDying()) return false;
		dynamic_cast<BobOmb*>(enemy)->Explode(); // Nổ ngay khi bị bắn
		fireball->setEntityDead();
		return true;
	}
	if (enemy->getEnemyType() == BUZZYBEETLE) {
		fireball->setEntityDead();
		if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("stomped.wav");
		enemy->setVelY(-400); // Buzzy Beetle bị bắn sẽ bay lên
		enemy->setState(JUMPING);
		SmokeEffect* smokeright = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{ 60, 120 });
		globalGameEngine->addEffect(smokeright);
		SmokeEffect* smokeleft = new SmokeEffect(Vector2{ enemy->getCenter().x, enemy->getTop() }, Vector2{ -60, 120 });
		globalGameEngine->addEffect(smokeleft);
	}
	CollisionType Colltype = fireball->CheckCollision(*enemy);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	enemy->CollisionWithFireball(fireball);
	return true;
}

bool EnemyEnemyInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Enemy* enemy1 = dynamic_cast<Enemy*>(entityA);
	Enemy* enemy2 = dynamic_cast<Enemy*>(entityB);

	if (!enemy1 || !enemy2 || enemy1->getCollisionAvailable() == false || enemy2->getCollisionAvailable() == false)
		return false;
	if (enemy1->getEnemyType() != SHELL && enemy2->getEnemyType() != SHELL)
		return false;
	CollisionType Colltype = enemy1->CheckCollision(*enemy2);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	//enemy2->attacked(enemy1->getDir());
	// enemy1 (shell) attack enemy
	if (enemy1->getEnemyType() == SHELL) {
		if (enemy1->getIsKicked())
			enemy2->stomped();
	}
	else {
		if (enemy2->getIsKicked())
			enemy1->stomped();
	}
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
		if (block && block->getBlockType() == COINBLOCK)
			return std::make_unique<PlayerCoinBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<PlayerBrickInfo>();
		if (block && block->getBlockType() == CLOUDBLOCK)
			return std::make_unique<PlayerCloudBlockInfo>();
		if (block && block->getBlockType() == NOTEBLOCK)
			return std::make_unique<PLayerNoteBlockInfo>();
		if (block && block->getBlockType() == ROTATINGBLOCK)
			return std::make_unique<PlayerRotatingBlockInfo>();
		return std::make_unique<PlayerBlockInfo>();
	}
	if (typeA == ENEMY && typeB == BLOCK)
	{
		if (block && block->getBlockType() == FLOOR)
			return std::make_unique<PlayerFloorInfo>();
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

	if (typeA == ENEMY_FIREBALL && typeB == CHARACTER) {
		return std::make_unique<FireBallPlayerInfo>();
	}
	if (typeA == FIREBALL && typeB == ENEMY) {
		return std::make_unique<FireBallEnemyInfo>();
	}
	if (typeA == FIREBALL && typeB == BLOCK) {
		if (block && block->getBlockType() == ITEMBLOCK)
			return std::make_unique<FireBallItemBlockInfo>();
		if (block && block->getBlockType() == BRICK)
			return std::make_unique<FireBallBrickInfo>();

		return std::make_unique<FireBallBlockInfo>();
	}
	if (typeA == ENEMY_FIREBALL && typeB == BLOCK) {
		return std::make_unique<EnemyFireBallBlockInfo>();
	}
	if (typeA == ENEMY && typeB == ENEMY) {
		return std::make_unique<EnemyEnemyInfo>();
	}
	return nullptr;
}


bool CollisionInterface::HandleCollision(Entity* entityA, Entity* entityB)
{

	if (!CheckCollisionRecs(entityA->getRect(), entityB->getRect()))
		return false;
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

bool PlayerRotatingBlockInfo::HandleCollision(Entity* entityA, Entity* entityB)
{
	Character* character = dynamic_cast<Character*>(entityA);
	RotatingBlock* block = dynamic_cast<RotatingBlock*>(entityB);

	if (!character || !block || !character->getCollisionAvailable())
		return false;
	CollisionType Colltype = character->CheckCollision(*block);
	if (Colltype == COLLISION_TYPE_NONE)
		return false;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		if (block->getActive() == false) {
			character->setPosition(Vector2{ character->getX(), block->getY() + block->getHeight() });
			character->setVelY(0);
			block->Activate();
		}
		break;
	case COLLISION_TYPE_SOUTH:
		if (block->getActive() == false) {
			character->setPosition(Vector2{ character->getX(), block->getY() - character->getHeight() });
			character->setState(ON_GROUND);
			character->setVelY(0);
		}
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
