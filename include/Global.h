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
	IDLING

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
	SPIKE,
	PIPE,
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
	KOOPATROOPA,
	PIRANHA,
	SHELL
};

enum GOOMBA_TYPE {
	BROWN_GOOMBA,
	RED_GOOMBA,
	REDPARA_GOOMBA,
	BROWNPARA_GOOMBA,
	MICRO_GOOMBA,
};

enum KOOPA_TROOPA_TYPE {
	GREEN_KoopaTroopa,
	RED_KoopaTroopa,
	GREENPARA_KoopaTroopa,
	REDPARA_KoopaTroopa
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