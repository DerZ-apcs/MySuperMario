#include "../include/MediatorCollision.h"
#include "../include/Character.h"

void MediatorCollision::HandlePlayerWithTiles(Character*& character, Tile*& tile, CollisionType Colltype)
{
	if (Colltype == COLLISION_TYPE_NONE)
		return;
	switch (Colltype) {
	case COLLISION_TYPE_NORTH:
		character->setPosition(Vector2{ character->getX(), tile->getY() + tile->getHeight() });
		character->setVelY(0);
		//state = FALLING;
		break;
	case COLLISION_TYPE_SOUTH:
		character->setPosition(Vector2{ character->getX(), tile->getY() - character->getHeight() });
		character->setState(ON_GROUND);
		character->setVelY(0);
		break;
	case COLLISION_TYPE_EAST:
		character->setPosition(Vector2{ tile->getX() - character->getWidth(), character->getY()});
		character->setVelX(0);
		break;
	case COLLISION_TYPE_WEST:
		character->setPosition(Vector2{ tile->getX() + tile->getWidth(), character->getY() });
		character->setVelX(0);
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

// Check Fireball vs Tile, Character vs Fire
void MediatorCollision::HandleCollision(Entity* entity1, Entity* entity2)
{
	/*Mario* isMario_1 = dynamic_cast<Mario*>(entity1);
	Mario* isMario_2 = dynamic_cast<Mario*>(entity2);*/
	Character* isCharacter_1 = dynamic_cast<Character*>(entity1);
	Character* isCharacter_2 = dynamic_cast<Character*>(entity1);

	FireBall* isFireBall_1 = dynamic_cast<FireBall*>(entity1);
	FireBall* isFireBall_2 = dynamic_cast<FireBall*>(entity2);

	Tile* isTile_1 = dynamic_cast<Tile*>(entity1);
	Tile* isTile_2 = dynamic_cast<Tile*>(entity2);

	if ((isCharacter_1 && isTile_2) || (isCharacter_2 && isTile_1)) {
		CollisionType CollType = isCharacter_1 ? isCharacter_1->CheckCollision(*isTile_2) : isCharacter_2->CheckCollision(*isTile_1);
		if (isCharacter_1)
			HandlePlayerWithTiles(isCharacter_1, isTile_2, CollType);
		else 
			HandlePlayerWithTiles(isCharacter_2, isTile_1, CollType);
	}
	else if ((isFireBall_1 && isTile_2) || (isFireBall_2 && isTile_1)) {
		CollisionType CollType = isFireBall_1 ? isFireBall_1->CheckCollision(*isTile_2) : isFireBall_2->CheckCollision(*isTile_1);
		if (isFireBall_1)
			HandleFireballWithTIles(isFireBall_1, isTile_2, CollType);
		else
			HandleFireballWithTIles(isFireBall_2, isTile_1, CollType);
	}
}
