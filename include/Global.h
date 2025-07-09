#ifndef GLOBAL_H
#define GLOBAL_H
#include "../include/ResourceManager.h"
#include "../include/Setting.h"
#include "../include/Singleton.h"
#include <map>

extern ResourceManager& RESOURCE_MANAGER;
extern Setting& SETTING;

enum EntityType {
	CHARACTER,
	ENEMY,
	ITEM,
	FIREBALL,
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
	STATE_IS_DYING,
	STATE_SHELL

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
	FLOOR,
	BRICK, // breakable
	SOLIDBLOCK, // unmovable, unbreakable
	MOVINGBLOCK,
	ITEMBLOCK,
	HIDDEN,
	TEMPBLOCK,
	DECOR
};


enum ITEM_TYPE {
	COIN,
	MUSHROOM,
	SUPERLEAF,
	FLOWER,
	STAR
};

enum ENEMY_TYPE {
	GOOMBA,
	KOOPA,
	BULLET,
	REX,
	PIRANHA,
	SHELL
};

enum GOOMBA_TYPE {
	NORMAL_GOOMBA,
	FLYING_GOOMBA
};

enum KOOPA_TROOPA_TYPE {
	NORMAL_KOOPA,
	FLYING_KOOPA
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

enum FireBallType {
	CHARACTER_FIREBALL,
	ENEMY_FIREBALL
};

enum MushroomType {
	GREENMUSHROOM, // Lives
	REDMUSHROOM, // Super
};

enum FlowerType {
	FIRE_FLOWER
};
enum StarType {
	YELLOW_STAR
};

enum CoinType {
	BLOCK_COIN,
	STATIC_COIN
};
#endif