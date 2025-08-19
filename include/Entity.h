#ifndef ENTITY_H
#define ENTITY_H
#include "../include/Singleton.h"
#include "../include/ResourceManager.h"
#include "../include/Direction.h"
#include "../include/Collision.h"
#include "../include/Global.h"
#include "../include/json.hpp"
#include <string>
#include <raylib.h>
#include <external/cgltf.h>
using nlohmann::json;

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
	Rectangle rect;
	const float GRAVITY = 800; // Gravity for all 
	const float accelerationX = 400;
	std::string Entity_name;

	bool isjumping;
	bool gravityAvailable = true;
	bool collisionAvailable;
	bool dead;

	Collision CollNorth;
	Collision CollSouth;
	Collision CollEast;
	Collision CollWest;
public:

	Entity();
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex, std::string name);
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state,
		Texture2D tex, float FrameTime, int MaxFrame, Color color);
	Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, float FrameTime, int MaxFrame, Color color);
	virtual ~Entity() = default;
	virtual void clone(const Entity& entity); // clone the entity
	virtual void Update();
	virtual void draw();
	virtual void HandleInput();
	virtual void updateCollision(); // update 4 rect in 4 sides
	virtual void UpdateTexture();
	virtual CollisionType CheckCollision(const Entity& entity) const; // check the collision of 4 rects with others

	bool isOnGround() const;
	virtual void RunLeft();
	virtual void RunRight();
	virtual void Jumping();
	// Setter
	void setPosition(Vector2 pos);
	void setX(float x);
	void setY(float y);

	void setSize(Vector2 sz);
	void setWidth(float width);
	void setHeight(float height);

	void setVel(Vector2 vel);
	void setVelX(float velx);
	void setVelY(float vely);

	void setState(EntityState state);
	void setColor(Color color);
	void setTexture(Texture2D tex);

	bool isDead() const;
	void setEntityDead();
	void setJumping(bool value);
	void setDirection(Direction dir);
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

	virtual EntityType getEntityType() const = 0;
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

	float getCenterX() const;
	float getCenterY() const;
	float getBottom() const;
	float getLeft() const;
	float getRight() const;
	float getTop() const;

	void setCollisionAvailable(bool collisionAvailable);
	void setGravityAvailable(bool gravityAvailable);
	bool getCollisionAvailable();
	bool getGravityAvailable();

	// for load/save game
	virtual void saveEntity(json& j) const;
	virtual void loadEntity(const json& j);
};	
#endif