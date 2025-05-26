#ifndef ENTITY_H
#define ENTITY_H
#include "../include/ResourceManager.h"
#include "../include/Direction.h"
#include "../include/EntityState.h"
#include "../include/Clock.h"
#include "../include/Collision.h"
#include <string>
#include <raylib.h>

class Entity {
protected:
	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Direction direction;
	EntityState state;
	Color color;
	int maxFrame;
	int currFrame;
	float frameTime;
	float frameAcum;
	Texture2D texture;

	const float GRAVITY = 800;
	std::string Entity_name;

	Collision CollNorth;
	Collision CollSouth;
	Collision CollEast;
	Collision CollWest;
public:

	Entity();
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex, std::string name);
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state,
		Texture2D tex, float FrameTime, int MaxFrame);
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, float FrameTime, int MaxFrame);
	virtual void Update();
	virtual void draw();
	virtual void HandleInput();
	virtual void UpdateTexture();
	virtual void updateCollision();
	virtual CollisionType CheckCollision(Entity* entity);

	bool isOnGround() const;
	virtual void RunLeft();
	virtual void RunRight();
	virtual void Jumping();
	// Setter
	void setPosition(Vector2 pos);
	void setSize(Vector2 sz);
	void setVel(Vector2 vel);
	void setState(EntityState state);
	// Getter
	Vector2& getPosition();
	float getX() const;
	float getY() const;
	Vector2 getCenter() const;

	Vector2& getSize();
	float getWidth() const;
	float getHeight() const;

	Vector2& getVelocity();
	float getVelX() const;
	float getVelY() const;

	EntityState getState() const;
	Direction getDir() const;
	// frame control
	int getMaxFrame() const;
	int getCurrFrame() const;
	float getFrameTime() const;
	float getFrameAcum() const;
	Texture2D getCurrTexture() const;
	std::string getName() const;

	Rectangle getRect() const;
	Color& getColor();

};	
#endif