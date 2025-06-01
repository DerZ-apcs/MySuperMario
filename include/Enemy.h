#ifndef ENEMY_H
#define ENEMY_H
#include "../include/Entity.h"
#include "../include/Mario.h"
class Enemy : public Entity {
protected:

public:
	Enemy();
	Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction dirction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color);
	~Enemy();
	virtual void CollisionWithCharacter();
	bool isDying();
	void Update() override;
	void draw() override;
	void updateCollision() override;
	//virtual void AutoMoving();
};
#endif