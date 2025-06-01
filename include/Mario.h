#ifndef MARIO_H
#define MARIO_H
#include <raylib.h>
#include "../include/Entity.h"
#include "../include/FireBall.h"
#include "../include/Tile.h"
#include <string>
#include <list>

enum MARIO_TYPE {
	STATE_SMALL,
	STATE_SUPER,
	STATE_FIRE_BALL
};

class Mario: public Entity {
private:
	//ResourceManager& resourceManager;
	MARIO_TYPE Mario_State;
	SPRITE_STATE Mario_sprite;
	SPRITE_STATE LastStateb4Transition;
	const float maxspeedX = 500;
	const float accelerationX = 600;
	//Clock TimeUpdate;
	const float GRAVITY = 800;
	const float maxSpeedY = 600;
	// transitioning
	float transitioningFrameTime;
	float transitioningFrameAcum;
	int transitionSteps;
	int transitionCurrentFrame;
	int transitionCurrentFramePos;
	const int transitionFrameOrder[11] = { 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 };
	const int reversedTransitionFrameOrder[11] = { 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0 };
	const int SuperToFlowerTransitionFrameOrder[10] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };

	std::list<FireBall*> fireballs;
	bool isDucking;
	bool isThrowing;
public:
	Mario();
	Mario(Vector2 nposition, Vector2 nsize, MARIO_TYPE type);
	~Mario();
	void HandleTileCollision(const Tile tile, CollisionType Colltype);
	void RunLeft() override;
	void RunRight() override;
	void Jumping() override;
	void Ducking();
	void Standing();
	void Update();
	void draw();
	void HandleInput();
	void updateCollision() override;
	void UpdateTexture();
	bool isOnGround() const;

	void TransitionToSuper();
	void TransitionToSmall();
	void TransitionToFire();
	void TransitionMarioState();
	
	void ThrowingFireBalls();
	std::list<FireBall*> *getFireBalls();
	// getter
	float getAccelerationX() const;
	void setLastStateBeforeTransition(SPRITE_STATE lastState);
};
#endif