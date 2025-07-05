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
	STATE_TRANSITIONING_FROM_SMALL_TO_SUPER,
	STATE_TRANSITIONING_FROM_SUPER_TO_SMALL,
	STATE_TRANSITIONING_FROM_SMALL_TO_FIREBALL,
	STATE_TRANSITIONING_FROM_SUPER_TO_FIREBALL,
	STATE_TRANSITIONING_FROM_FIREBALL_TO_SMALL,
	STATE_IS_ACTIVE,
	STATE_IS_DYING
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
	STATE_FIRE_BALL
};

#endif