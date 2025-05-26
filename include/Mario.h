#ifndef MARIO_H
#define MARIO_H
#include <raylib.h>
#include "../include/Entity.h"
#include <string>

enum MARIO_TYPE {
	STATE_SMALL,
	STATE_SUPER,
	STATE_FIRE_BALL
};
enum MARIO_SPRITE {
	NORMAL,
	STATE_TRANSITIONING_FROM_SMALL_TO_SUPER,
	STATE_TRANSITIONING_FROM_SUPER_TO_SMALL
};
enum TextureMario {
	SMALL,
	SUPER,
	TRANSITIONING
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

	TextureMario textureSprite;
	int pos_onGroundY;
	bool isDucking;
public:
	Mario();
	Mario(Vector2 nposition, Vector2 nsize, Vector2 nvel, MARIO_TYPE Type0, EntityState playerState, Direction ndirection);
	~Mario();
	void RunLeft();
	void RunRight();
	void Jumping();
	void Ducking();
	void Standing();
	void Update();
	void draw();
	void HandleInput();
	void UpdateTexture();
	bool isOnGround() const;
	void TransitionToSuper();
	void TransitionToSmall();
	void TransitionMarioState();
	// getter
	
};
#endif