#ifndef MEDIATORCOLLISION_H
#define MEDIATORCOLLISION_H
#include "../include/Entity.h"
//#include "../include/Character.h"
#include "../include/Tile.h"
#include "../include/FireBall.h"

class Character;
class FireBall;
class Tile;

class MediatorCollision {
private:
	void HandlePlayerWithTiles(Character*& character, Tile*& tile, CollisionType Colltype);
	void HandleFireballWithTIles(FireBall*& fireball, Tile*& tile, CollisionType Colltype);
public:
	void HandleCollision(Entity* entity1, Entity* entity2);
};
#endif