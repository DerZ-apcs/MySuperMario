#ifndef CHARACTER_H
#define CHARACTER_H

#include "../include/Entity.h"
#include "../include/Global.h"
#include <../include/TextEffect.h>
#include <../include/Item.h>
#include "../include/InputHandler.h"
#include "raymath.h"
#include <list>

class Item;
class Enemy;
class Blocks;
class FireBall;
class EnemyFireBall;
class GameEngine;
class MovingBlock;

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
	Character
	
	
	
	(Vector2 pos, Vector2 sz, CharacterState characterstate, CharacterType characterType);
	virtual ~Character();
	EntityType getEntityType() const override;
	virtual CharacterType getCharacterType() const = 0;
	virtual void resetInGame();
	virtual void reset();
	virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;
	virtual const CharacterState& getCharacterState() const;
	void setMovingBlockStandOn(MovingBlock* block);
	MovingBlock* getMovingBlockStandOn() const;

	bool isInvicible() const;
	bool isImmortal() const;
	bool isDucking() const;
	bool isLostLife() const;
	bool isIdle() const;
	bool isStandingUp() const;
	bool isJumping() const;

	void setPlayerid(int id) { playerId = id; }
	int getPlayerid() const { return playerId; }
	int getLives() const;
	int getCoins() const;
	int getScores() const;
	bool isHolding() const;
	bool getVictory() const;
	bool getExitLevel() const;
	float getSinkingTime() const;

	void setLostLife(bool lostLife);
	void setSinkingTime(float sinkingTime);
	void setLives(int lives);
	void setCoins(int coins);
	void setScores(int scores);
	void setDucking(bool ducking);
	void setCharacterState(CharacterState characterState);
	void setHolding(bool holding);
	void lostSuit();
	void setVictory(bool victory);
	void eatGreenMushrooms();
	void eatRedMushrooms();
	void eatStar();
	void eatFireFlower();
	
	void StartTransition(const std::vector<int>& frameOrder, int steps);

	float getMAX_WALK_SPEED_X() const { return MAX_WALK_SPEED_X; }
	float getMAX_RUN_SPEED_X() const { return MAX_RUN_SPEED_X; }
	float getMAXSPEED_Y() const { return MAXSPEED_Y; }
	float getACCEL_X() const { return ACCEL_X; }
	float getDECEL_X() const { return DECEL_X; }
	float getCHARACTER_GRAVITY() const { return CHARACTER_GRAVITY; }
	
	virtual void ReleaseRunFast();
	virtual void RunFast();
	virtual void RunLeft();
	virtual void RunRight();
	virtual void Jumping();
	virtual void Standing();
	virtual void Ducking();
	virtual void Update() override;
	virtual void draw() override;
	virtual void HandleInput() override;
	void HandleInput(int leftKey, int rightKey, int upKey, int downKey, int fireKey);
	void HandleInput(InputHandler& inputHandler1, InputHandler& inputHandler2);
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
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
protected:
	int playerId = 0; // 0 for player1, 1 for player2
	struct TransitionFrame {
		std::string textureKey;
		Vector2 size;
		CharacterState FinalState;
		int Max_frame;
	};
	std::vector<TransitionFrame> transitionFrames;
	std::vector<TransitionFrame> transitionFramesLuigi;
	std::vector<TransitionFrame> transitionFramesToad;
	std::vector<TransitionFrame> transitionFramesPeach;
	std::vector<TransitionFrame> transitionFramesMarisa;
	Phase phase;
	CharacterType characterType;
	MovingBlock* movingBlockStandOn = nullptr; // for standing up on moving block
	Vector2 specificVelocity; // specific velocity for character
	bool lostLife;
	bool isducking;
	int scores;
	int coins;
	int lives;
	float invicibleStarTime;
	float sinkingTime;

	bool takeDamage = true;
	bool holding;
	bool isThrowing;

	float timeNoTakeDamage = 0.f;
	float countThrowTime;
	float countImmortalTime;
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
	std::list<FireBall*> fireballs;

	const float DEAD_PLAYER_INITIAL_VELOCITY = 500.f;
	const float DEAD_PLAYER_GRAVITY = 1000.f;

	const float Max_walk_velocity = 400.f;
	const float jet_stomp_velocity = -300.f;

	const float star_invicible_time = 12.f;
	const float transform_time = 1.f;

	// mỗi nhân vật sẽ có các thông số khác nhau
	float MAX_WALK_SPEED_X; 
	float MAX_RUN_SPEED_X;
	float MAXSPEED_Y;
	float ACCEL_X;
	float DECEL_X;
	float CHARACTER_GRAVITY;
	//
	bool victory = false;
	bool exitlevel = false;
	bool lostSuitTrigger = false;
};
#endif