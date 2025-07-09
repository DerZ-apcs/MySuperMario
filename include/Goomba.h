//#ifndef GOOMBA_H
//#define GOOMBA_H
//#include "../include/Enemy.h"
//
//class Goomba : public Enemy {
//private:
//	const int SCORE_STOMP_GOOMBA = 100;
//	const float FLYINGGOOMBA_JUMP_INTERVAL = 1.0f;
//	const float GOOMBA_SPEED = 100.0f;
//	const float FLYINGGOOMBA_SPEED = 100.0f;
//	const float FLYINGGOOMBA_JUMP_SPEED = 500.0f;
//
//	const float TIME_PER_JUMP = 2.f;
//	GOOMBA_TYPE type;
//	bool canJump;
//	float jumpTime;
//public:
//	Goomba(GOOMBA_TYPE type = NORMAL_GOOMBA, Vector2 pos = {0, 0}, Direction dir = RIGHT);
//	~Goomba();
//	ENEMY_TYPE getEnemyType() const override;
//	void Update() override;
//	void UpdateTexture() override;
//	void attacked(Direction direction) override;
//	void stomped() override;
//	void draw() override;
//};
//
//#endif

#ifndef GOOMBA_H
#define GOOMBA_H
#include "../include/Enemy.h"

class Goomba : public Enemy {
private:
    float pauseTimer;
    bool isPaused;
    float detectMarioRange;
    float collisionTimer;
    bool beattacked;
public:
    bool isAttacked() const;
    ENEMY_TYPE getEnemyType() const;
    Goomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void attacked(Direction direction) override;
    float getScores() const override;
    void stomped() override;
    //void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    //void HandleTileCollision(const Tile& tile, CollisionType collType) override;*/
};

class FlyingGoomba : public Goomba {
private:
    float jumpTimer; // Timer để kiểm soát tần suất nhảy
    float detectMarioRange;
    float collisionTimer;
public:
    ENEMY_TYPE getEnemyType() const;
    FlyingGoomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
    float getScores() const override;
    //void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

#endif
