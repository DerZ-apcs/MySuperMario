#ifndef COLLISION_H
#define COLLISION_H
#include <raylib.h>
enum CollisionType {
	COLLISION_TYPE_NONE = 0,
	COLLISION_TYPE_SOUTH,
	COLLISION_TYPE_NORTH,
	COLLISION_TYPE_WEST,
	COLLISION_TYPE_EAST,

	COLLISION_TYPE_COLLIDED,
	COLLISION_TYPE_FIREBALL
};
class Collision {
private:
	Vector2 pos;
	Vector2 size;
	Color color;
public:
	Collision();
	Collision(Vector2 pos, Vector2 sz, Color color);
	~Collision();

	void draw() const;
	CollisionType checkCollision(Rectangle& rect) const;
	// setter
	void setPos(Vector2 pos);
	void setX(float x);
	void setY(float y);

	void setSize(Vector2 size);
	void setWidth(float width);
	void setHeight(float height);
	void setColor(Color color);

	// getter
	Vector2& getPos();
	float getX() const;
	float getY() const;

	Vector2& getSize();
	float getWidth() const;
	float getHeight() const;

	Color& getColor();
	Rectangle getRect() const;
};
#endif