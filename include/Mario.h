#ifndef MARIO_H
#define MARIO_H
#include <raylib.h>
#include "../include/Character.h"
#include "../include/FireBall.h"
#include "../include/Tile.h"
#include <string>
#include <list>

class Mario: public Character {
private:
	/*CharacterState Mario_State;
	SPRITE_STATE Mario_sprite;*/
	//SPRITE_STATE LastStateb4Transition;
	const float maxspeedX = 550;
	const float maxSpeedY = 550;

	//std::list<FireBall*> fireballs;
public:
	Mario();
	Mario(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Mario();
	CharacterType getCharacterType() const override;
	//void HandleTileCollision(const Tile tile, CollisionType Colltype) override;
	void RunLeft() override;
	void RunRight() override;
	void Jumping() override;
	//void Ducking() override;
	//void Standing() override;
	//void Update() override;
	//void draw() override;
	//void HandleInput() override;
	//void updateCollision() override;
	//void UpdateTexture() override;

	//void TransitionToSuper() override;
	//void TransitionToSmall() override;
	//void TransitionToFire() override;
	//void TransitionMarioState() override;
	
	//void ThrowingFireBalls() override;
	//std::list<FireBall*>* getFireBalls() override;
	// getter
	//float getAccelerationX() const;
	//void setLastStateBeforeTransition(SPRITE_STATE lastState);

	void reset() override;
};
#endif