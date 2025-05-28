#include "../include/Collision.h"

Collision::Collision():
	Collision(Vector2{ 0, 0 }, Vector2{ 5, 5 }, Color{ 255, 255, 255, 255 }) {
}

Collision::Collision(Vector2 pos, Vector2 sz, Color color):
	pos(pos), size(sz), color(color) {
}

Collision::~Collision() = default;

void Collision::draw() const 
{
	DrawRectangle(pos.x, pos.y, size.x, size.y, color);
}

CollisionType Collision::checkCollision(Rectangle& rect) const
{
	return CheckCollisionRecs(rect, getRect()) ? COLLISION_TYPE_COLLIDED : COLLISION_TYPE_NONE;
}

void Collision::setPos(Vector2 pos)
{
	this->pos = pos;
}

void Collision::setX(float x)
{
	this->pos.x = x;
}

void Collision::setY(float y)
{
	this->pos.y = y;
}

void Collision::setSize(Vector2 size)
{
	this->size = size;
}

void Collision::setWidth(float width)
{
	this->size.x = width;
}

void Collision::setHeight(float height)
{
	this->size.y = height;
}

void Collision::setColor(Color color)
{
	this->color = color;
}

Vector2& Collision::getPos()
{
	return this->pos;
}

float Collision::getX() const
{
	return this->pos.x;
}

float Collision::getY() const
{
	return this->pos.y;
}

Vector2& Collision::getSize()
{
	return this->size;
}

float Collision::getWidth() const
{
	return this->size.x;
}

float Collision::getHeight() const
{
	return this->size.y;
}

Color& Collision::getColor()
{
	return this->color;
}

Rectangle Collision::getRect() const
{
	return Rectangle{ pos.x, pos.y, size.x, size.y };
}