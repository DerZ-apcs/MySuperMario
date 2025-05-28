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
enum MARIO_SPRITE {
	NORMAL,
	STATE_TRANSITIONING_FROM_SMALL_TO_SUPER,
	STATE_TRANSITIONING_FROM_SUPER_TO_SMALL,
	STATE_TRANSITIONING_FROM_SMALL_TO_FLOWER
};
enum TextureMario {
	SMALL,
	SUPER,
	TRANSITIONING,
	FLOWER
};
class Mario: public Entity {
private:
	MARIO_TYPE Mario_State;
	MARIO_SPRITE Mario_sprite;
	const float maxspeedX = 500;
	const float accelerationX = 700;
	//Clock TimeUpdate;
	const float GRAVITY = 800;
	const float maxJumping = 400;
	const float maxSpeedY = 500;
	// transitioning
	float transitioningFrameTime;
	float transitioningFrameAcum;
	int transitionSteps;
	int transitionCurrentFrame;
	int transitionCurrentFramePos;
	const int transitionFrameOrder[11] = { 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 };
	const int reversetTransitionFrameOrder[11] = { 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0 };

	std::list<FireBall*> fireballs;
	TextureMario textureSprite;
	int pos_onGroundY;
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
};
#endif