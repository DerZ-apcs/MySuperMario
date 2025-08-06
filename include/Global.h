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
	SINKING,
	STATE_IS_DYING,
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
	LUIGI,
	PEACH,
	MARISA,
	TOAD
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
	CLOUDBLOCK, // phase through
	SOLIDBLOCK, // unmovable, unbreakable
	MOVINGBLOCK,
	ITEMBLOCK, // carry items
	HIDDEN, 
	TEMPBLOCK,
	DECOR, // for decor, not collision
	COINBLOCK, // coin when hit
	NOTEBLOCK,// note block
	ROTATINGBLOCK
};

enum BOUNCE_DIRECTION {
	BOUNCE_UP,
	BOUNCE_DOWN,
	BOUNCE_LEFT,
	BOUNCE_RIGHT,
	NO_BOUNCE
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
	PARAKOOPA,
	BULLET,
	REX,
	PIRANHA,
	SHELL,
	MUNCHER,
	BOBOMB,
	SPINY,
	BUZZYBEETLE,
	DRYBONES,
	BOSS
};

enum GOOMBA_TYPE {
	NORMAL_GOOMBA,
	FLYING_GOOMBA
};

enum KOOPA_TYPE {
	YELLOW_KOOPA,
	GREEN_KOOPA,
	RED_KOOPA,
	BLUE_KOOPA
};

enum PARAKOOPA_TYPE {
	YELLOW_PARAKOOPA,
	GREEN_PARAKOOPA,
	RED_PARAKOOPA,
	BLUE_PARAKOOPA
};

enum BULLET_TYPE {
	NORMAL_BULLET,
	FIREBALL_BULLET
};


enum PIRANHA_TYPE {
	NORMAL_PIRANHA,
	FIRE_PIRANHA,
	HOMING_PIRANHA,
	JUMPING_PIRANHA,
	RAPIDFIRE_PIRANHA

};

enum PowerUpState {
	EMERGING,
	ACTIVE,
	CONSUMED
};

enum SHELL_TYPE {
	GREEN_SHELL,
	RED_SHELL
};

enum MushroomType {
	// Super 0.
	REDMUSHROOM,
	GREENMUSHROOM, // Lives 1
};

enum FlowerType {
	FIRE_FLOWER // 0
};
enum MoonType {
	NORMAL_MOON // 0
};
enum StarType {
	YELLOW_STAR, // 0
	BLUE_STAR // 1
};

enum CoinType {
	STATIC_COIN, // 0
	BLOCK_COIN // 1
};
#endif