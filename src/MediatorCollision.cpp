#include "../include/MediatorCollision.h"

void MediatorCollision::HandlePlayerWithTiles(Mario*& mario, Tile*& tile, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		mario->setPosition(Vector2{ mario->getX(), tile->getY() + tile->getHeight() });
		mario->setVelY(0);
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		mario->setPosition(Vector2{ mario->getX(), tile->getY() - mario->getHeight() });
		mario->setState(ON_GROUND);
		mario->setVelY(0);
		break;
	case COLLISION_TYPE_EAST:
		mario->setPosition(Vector2{ tile->getX() - mario->getWidth(), mario->getY()});
		mario->setVelX(0);
		break;
	case COLLISION_TYPE_WEST:
		mario->setPosition(Vector2{ tile->getX() + tile->getWidth(), mario->getY() });
		mario->setVelX(0);
		break;
	default:
		break;
	}
}

void MediatorCollision::HandlePlayerWithBrick(Mario*& mario, Brick*& brick, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE) { return; }
	if (brick->getBroken()) return; // If the brick is broken, no collision handling needed

	switch (Colltype) {
	case COLLISION_TYPE_SOUTH:
		// lands on top of brick
		mario->setPosition(Vector2{ mario->getX(), brick->getY() - mario->getHeight() });
		mario->setVelY(0);
		mario->setState(ON_GROUND);
		break;

	case COLLISION_TYPE_NORTH:
		// hits brick from below
		mario->setPosition(Vector2{ mario->getX(), brick->getY() + brick->getHeight() });
		mario->setVelY(100);
		brick->setBroken(true);
		break;

	case COLLISION_TYPE_EAST:
		mario->setPosition(Vector2{ brick->getX() - mario->getWidth(), mario->getY() });
		mario->setVelX(0);
		break;

	case COLLISION_TYPE_WEST:
		mario->setPosition(Vector2{ brick->getX() + brick->getWidth(), mario->getY() });
		mario->setVelX(0);
		break;

	default:
		break;
	}
}

void MediatorCollision::HandleFireballWithTIles(FireBall*& fireball, Tile*& tile, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) 
	{
	case COLLISION_TYPE_NORTH:
		fireball->setPosition(Vector2{ fireball->getX(), tile->getY() + tile->getHeight() });
		fireball->setVelY(0);
		break;
	case COLLISION_TYPE_SOUTH:
		fireball->setPosition(Vector2{ fireball->getX(), tile->getY() - fireball->getHeight()});
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

void MediatorCollision::HandlePowerItemWithTiles(PowerItem*& item, Tile*& tile, CollisionType Colltype) {
	if (item->getItemState() != ACTIVE) return; 
	if (Colltype == COLLISION_TYPE_NONE) return;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		item->setPosition(Vector2{ item->getX(), tile->getY() + tile->getHeight() });
		item->setVelY(0);
		printf("PowerItem collided with tile from north\n");
		break;
	case COLLISION_TYPE_SOUTH:
		item->setPosition(Vector2{ item->getX(), tile->getY() - item->getHeight() });
		item->setState(ON_GROUND);
		item->setVelY(0);
		printf("PowerItem collided with tile from south\n");
		break;
	case COLLISION_TYPE_EAST:
		item->setPosition(Vector2{ tile->getX() - item->getWidth(), item->getY() });
		item->setVelX(item->getVelX() * -1);
		break;
	case COLLISION_TYPE_WEST:
		item->setPosition(Vector2{ tile->getX() + tile->getWidth(), item->getY() });
		item->setVelX(item->getVelX() * -1);
		break;
	default:
		break;
	}
}

void MediatorCollision::HandlePlayerWithCoins(Mario*& mario, Coin*& coin, CollisionType Colltype) {
	if (Colltype == COLLISION_TYPE_NONE) { return; }
	if (coin->getCollected()) return; 

	coin->setCollected(true); // Mark 
}

void MediatorCollision::HandlePlayerWithPowerItem(Mario*& mario, PowerItem*& item, CollisionType Colltype) {
	if (Colltype == COLLISION_TYPE_NONE) { return; }
	if (item->getItemState() != ACTIVE) { return; }

	item->onConsume(*mario); 
}



//-------------------------

void MediatorCollision::HandleCollision(Entity* entity1, Entity* entity2)
{
	Mario* isMario_1 = dynamic_cast<Mario*>(entity1);
	Mario* isMario_2 = dynamic_cast<Mario*>(entity2);
	FireBall* isFireBall_1 = dynamic_cast<FireBall*>(entity1);
	FireBall* isFireBall_2 = dynamic_cast<FireBall*>(entity2);
	Brick* isBrick_1 = dynamic_cast<Brick*>(entity1);
	Brick* isBrick_2 = dynamic_cast<Brick*>(entity2);
	Tile* isTile_1 = dynamic_cast<Tile*>(entity1);
	Tile* isTile_2 = dynamic_cast<Tile*>(entity2);
	Coin* isCoin_1 = dynamic_cast<Coin*>(entity1);
	Coin* isCoin_2 = dynamic_cast<Coin*>(entity2);
	PowerItem* isPowerUp_1 = dynamic_cast<PowerItem*>(entity1);
	PowerItem* isPowerUp_2 = dynamic_cast<PowerItem*>(entity2);

	if ((isMario_1 && isBrick_2) || (isMario_2 && isBrick_1)) {
		CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isBrick_2) : isMario_2->CheckCollision(*isBrick_1);
		if (isMario_1)
			HandlePlayerWithBrick(isMario_1, isBrick_2, CollType);
		else
			HandlePlayerWithBrick(isMario_2, isBrick_1, CollType);
	}
	else if ((isMario_1 && isTile_2) || (isMario_2 && isTile_1)) {
		CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isTile_2) : isMario_2->CheckCollision(*isTile_1);
		if (isMario_1)
			HandlePlayerWithTiles(isMario_1, isTile_2, CollType);
		else 
			HandlePlayerWithTiles(isMario_2, isTile_1, CollType);
	}
	else if ((isFireBall_1 && isTile_2) || (isFireBall_2 && isTile_1)) {
		CollisionType CollType = isFireBall_1 ? isFireBall_1->CheckCollision(*isTile_2) : isFireBall_2->CheckCollision(*isTile_1);
		if (isFireBall_1)
			HandleFireballWithTIles(isFireBall_1, isTile_2, CollType);
		else
			HandleFireballWithTIles(isFireBall_2, isTile_1, CollType);
	}
	else if ((isPowerUp_1 && isTile_2) || (isPowerUp_2 && isTile_1)) {
		CollisionType CollType = isPowerUp_1 ? isPowerUp_1->CheckCollision(*isTile_2) : isPowerUp_2->CheckCollision(*isTile_1);
		if (isPowerUp_1)
			HandlePowerItemWithTiles(isPowerUp_1, isTile_2, CollType);
		else
			HandlePowerItemWithTiles(isPowerUp_2, isTile_1, CollType);
	}
	else if ((isMario_1 && isCoin_2) || (isMario_2 && isCoin_1)) {
		CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isCoin_2) : isMario_2->CheckCollision(*isCoin_1);
		if (isMario_1)
			HandlePlayerWithCoins(isMario_1, isCoin_2, CollType);
		else
			HandlePlayerWithCoins(isMario_2, isCoin_1, CollType);
	}
	else if ((isMario_1 && isPowerUp_2) || (isMario_2 && isPowerUp_1)) {
		CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isPowerUp_2) : isMario_2->CheckCollision(*isPowerUp_1);
		if (isMario_1)
			HandlePlayerWithPowerItem(isMario_1, isPowerUp_2, CollType);
		else
			HandlePlayerWithPowerItem(isMario_2, isPowerUp_1, CollType);
	}
}
