#ifndef ENEMY_H
#define ENEMY_H
#include "../include/Entity.h"
#include "../include/Mario.h"

class Character;
class FireBall;

class Enemy : public Entity {
protected:
	Vector2 boundary; // The x-axis range that enemy can move, y-axis for vertical plant
	float randomMoveTimer;

	const float DEAD_TIME = 0.5f;
	const float DEAD_INITIAL_VELOCITY_Y = 200.f;
	const float DEAD_INITIAL_VELOCITY_X = 100.f;
	const int ENEMY_POINT = 100;
	const float TIME_RANDOM_MOVE = 3.f;

public:
	Enemy();
	Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction dirction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color);
	Enemy(Vector2 pos, Vector2 size);
	virtual ~Enemy() = default;

	EntityType getEntityType() const override;

	virtual ENEMY_TYPE getEnemyType() const = 0;

	Direction getRandomDirection();
	virtual void setBoundary(Vector2 boundary);
	virtual const Vector2& getBoundary() const;

	virtual void stomped();
	virtual void attacked(Direction direction = RIGHT);
	virtual void kicked(Direction direction) {};
	void CollisionWithFireBall(FireBall* fireball);

	//virtual void CollisionWithCharacter();
	virtual void Update() override;
	virtual void draw() override;
	virtual void UpdateTexture() override;
	void updateCollision() override;
};
#endif