#ifndef CHARACTER_H
#define CHARACTER_H

#include "../include/Entity.h"
#include "../include/Global.h"
#include <../include/TextEffect.h>
#include <../include/Item.h>
#include "raymath.h"
#include <list>

class Item;
class Enemy;
class Blocks;
class FireBall;
class EnemyFireBall;
class GameEngine;

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
	EntityType getEntityType() const override;
	virtual CharacterType getCharacterType() const = 0;
	virtual void resetInGame();
	virtual void reset();
	virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;
	virtual CharacterState& getCharacterState();
	virtual CharacterState& getPrevCharacterState();

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
	bool getVictory() const;
	bool getExitLevel() const;

	void setLostLife(bool lostLife);
	
	//void transform(CharacterState newState);
	void setLives(int lives);
	void setCoins(int coins);
	void setScores(int scores);
	void setDucking(bool ducking);
	void setHolding(bool holding);
	void lostSuit();
	void setVictory(bool victory);
	void eatGreenMushrooms();
	void eatRedMushrooms();
	void eatStar();
	void eatFireFlower();
	
	void StartTransition(const std::vector<int>& frameOrder, int steps);

	virtual void RunLeft();
	virtual void RunRight();
	virtual void Jumping();
	virtual void Standing();
	virtual void Ducking();
	virtual void Update() override;
	virtual void draw() override;
	virtual void HandleInput() override;
	virtual void updateCollision() override;
	virtual void UpdateTexture() override;
	virtual void UpdateTransitioningTexture();
	float getAcclerationX() const;
	virtual void ThrowingFireBalls();
	

	void collisionWithItem(const Item* item);
	void collisionWithEnemy(Enemy* enemy, CollisionType CollType = COLLISION_TYPE_NORTH);
	void CollisionWithFireball(EnemyFireBall* fireball);
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
	struct TransitionFrame {
		std::string textureKey;
		Vector2 size;
		CharacterState FinalState;
		int Max_frame;
	};
	std::vector<TransitionFrame> transitionFrames;
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
	int throwFrameCounter = 6; // for throw
	int victoryFrameCounter = 30; // for victory
	std::vector<int> transitionFrameOrder;

	CharacterState Character_state;
	CharacterState PrevCharacter_state;
	SPRITE_STATE Character_sprite_State;
	std::list<FireBall*> fireballs;

	const float DEAD_PLAYER_INITIAL_VELOCITY = 500.f;
	const float DEAD_PLAYER_GRAVITY = 1000.f;

	const float Max_walk_velocity = 400.f;
	const float jet_stomp_velocity = -300.f;

	const float star_invicible_time = 12.f;
	const float transform_time = 1.f;

	const float MARIO_MAXSPEEDY = 550;
	const float MARIO_MAXSPEEDX = 550;
	const float LUIGI_MAXSPEEDY = 650;
	const float LUIGI_MAXSPEEDX = 500;

	bool victory = false;
	bool exitlevel;
	bool lostSuitTrigger = false;
};
#endif