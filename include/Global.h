#ifndef GLOBAL_H
#define GLOBAL_H
#include "../include/ResourceManager.h"
#include "../include/Setting.h"
#include "../include/Singleton.h"
#include <map>
#include <random>

extern ResourceManager& RESOURCE_MANAGER;
extern Setting& SETTING;

enum EntityType {
	CHARACTER,
	ENEMY,
	ITEM,
	FIREBALL,
	ENEMY_FIREBALL,
	EFFECT,
	BLOCK
};

enum EntityState {
	//IDLING,
	FALLING,
	JUMPING,
	ON_GROUND,
	IDLING,
	FLYING,
	STATE_IS_DYING

};
enum SPRITE_STATE {
	NORMAL,
	SMALL_TO_SUPER,
	SMALL_TO_FIRE,
	SUPER_TO_FIRE,
	FIRE_TO_SMALL,
	ANY_TO_STAR,
	STAR_TO_PREVIOUS
};
// Mario, luigi
enum CharacterType { 
	MARIO,
	LUIGI
};
// State: Small, Super, Fireball
enum CharacterState {
	STATE_SMALL,
	STATE_SUPER,
	STATE_FIRE,
	STATE_STAR,
	STATE_SUPERSTAR,
	STATE_FIRESTAR
};

//Block
enum BLOCK_TYPE {
	FLOOR, // only collision the upper
	BRICK, // breakable
	SOLIDBLOCK, // unmovable, unbreakable
	MOVINGBLOCK,
	ITEMBLOCK, // carry items
	HIDDEN, 
	TEMPBLOCK,
	DECOR, // for decor, not collision
	COINBLOCK, // coin when hit
	CLOUDBLOCK
};


enum ITEM_TYPE {
	COIN,
	MUSHROOM,
	FLOWER,
	STAR,
	POWERITEM,
	MOON
};

enum ENEMY_TYPE {
	GOOMBA,
	KOOPA,
	BULLET,
	REX,
	PIRANHA,
	SHELL,
	MUNCHER
};

enum GOOMBA_TYPE {
	NORMAL_GOOMBA,
	FLYING_GOOMBA
};

enum KOOPA_TYPE {
	YELLOW_KOOPA,
	GREEN_KOOPA
};

enum BULLET_TYPE {
	NORMAL_BULLET,
	FIREBALL_BULLET
};


enum PIRANHA_TYPE {
	RED_PIRANHA,
	RED_FIRE_PIRANHA,
	GREEN_PIRANHA,
	GREEN_FIRE_PIRANHA
};

enum SHELL_TYPE {
	GREEN_SHELL,
	RED_SHELL
};

enum MushroomType {
	// Super 1.
	REDMUSHROOM,
	GREENMUSHROOM, // Lives 2.
};

enum FlowerType {
	FIRE_FLOWER // 1
};
enum MoonType {
	NORMAL_MOON
};
enum StarType {
	YELLOW_STAR, // 1.
	BLUE_STAR // 2.
};

enum CoinType {
	STATIC_COIN, // 1.
	BLOCK_COIN // 2.
};

enum PowerUpState {
	EMERGING,
	ACTIVE
};
#endif