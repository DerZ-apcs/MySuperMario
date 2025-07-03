#ifndef CHARACTER_H
#define CHARACTER_H

#include "../include/Entity.h"
#include "../include/Global.h"
#include "../include/Tile.h"
#include "../include/MediatorCollision.h"
#include "raymath.h"
#include <list>

enum Phase {
	DEFAULT_PHASE,
	TRANSFORM_PHASE,
	DEAD_PHASE,
	EXIT_PHASE,
	ENTER_PHASE,
	CLEARLEVEL_PHASE
};

// Base class for all character
class Character : public Entity {
public:
	Character();
	Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 });
	Character(Vector2 pos, Vector2 sz, CharacterState characterstate);
	Character(Vector2 pos, Vector2 sz, CharacterState characterstate, CharacterType characterType);
	virtual ~Character();
	virtual EntityType getEntityType() const;
	virtual CharacterType getCharacterType() const = 0;
	virtual void resetInGame();
	virtual void reset();
	virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;
	virtual CharacterState& getCharacterState();

	bool isInvicible() const;
	bool isDucking() const;
	bool isLostLife() const;
	bool isIdle() const;
	bool isStandingUp() const;
	bool isJumping() const;

	int getLives() const;
	int getCoins() const;
	int getScores() const;
	bool isHolding() const;

	void setLostLife(bool lostLife);
	
	void transform(CharacterState newState);
	void setLives(int lives);
	void setCoins(int coins);
	void setScores(int scores);
	void setDucking(bool ducking);
	void setHolding(bool holding);
	void lostSuit();
	
	virtual void TransitionToSuper();
	virtual void TransitionToSmall();
	virtual void TransitionToFire();
	virtual void TransitionMarioState();

	virtual void HandleTileCollision(const Tile tile, CollisionType CollType);
	virtual void RunLeft() = 0;
	virtual void RunRight() = 0;
	virtual void Jumping() = 0;
	virtual void Standing();
	virtual void Ducking();
	virtual void Update() override;
	virtual void draw() override;
	virtual void HandleInput() override;
	virtual void updateCollision() override;
	virtual void UpdateTexture() override;
	float getAcclerationX() const;
	virtual void ThrowingFireBalls();
	
	virtual std::list<FireBall*>* getFireBalls();
	
	// helper struct to control texture
	struct AnimationKey {
		CharacterState character_state;
		EntityState entity_state;
		Direction direction;
		int frame;
		bool operator<(const AnimationKey& other) const {
			return std::tie(character_state, entity_state, direction, frame) <
				std::tie(other.character_state, other.entity_state, other.direction, other.frame);
		}
	};
protected:
	Phase phase;
	CharacterType characterType;
	bool lostLife;
	bool isducking;
	int scores;
	int coins;
	int lives;
	float invicibleStarTime;

	bool holding;
	bool isThrowing;
	Vector2 specificVelocity;

	float countThrowTime;
	float countImmortalTime;
	unsigned indexRender;
	vector<bool> renderImmortal;
	bool standingUp;

	float transitioningFrameTime;
	float transitioningFrameAcum;
	int transitionSteps;
	int transitionCurrentFrame;
	int transitionCurrentFramePos;
	const int transitionFrameOrder[11] = { 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 };
	const int reversedTransitionFrameOrder[11] = { 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0 };
	const int SuperToFlowerTransitionFrameOrder[10] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };

	CharacterState Character_state;
	SPRITE_STATE Character_sprite_State;
	//const float GRAVITY = 800;
	//const float accelerationX = 400;
	std::list<FireBall*> fireballs;
};
#endif