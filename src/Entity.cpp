#include "../include/Entity.h"

Entity::Entity() :
	Entity(Vector2{ 0, 0 }, Vector2{ 0, 0 }, Vector2{ 0, 0 }, RIGHT, IDLING, texture, 0.1f, 0, BLACK)
{
}

Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex, std::string name) :
	Entity(pos, sz, vel, dir, state, tex, 0.1, 0, BLACK)
{
}

Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state,
	Texture2D tex, float FrameTime, int MaxFrame, Color color) :
	position(pos), size(sz), velocity(vel), direction(dir), state(state), texture(tex),
	frameTime(FrameTime), maxFrame(MaxFrame), frameAcum(0), currFrame(0), color(color)
{
	CollNorth.setColor(color);
	CollEast.setColor(color);
	CollSouth.setColor(color);
	CollWest.setColor(color);
}

Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, float FrameTime, int MaxFrame, Color color) :
	position(pos), size(sz), velocity(vel), direction(dir), state(state), frameTime(FrameTime), maxFrame(MaxFrame), color(color),
	CollNorth(Vector2{ pos.x + size.x / 2 - 5, pos.y }, Vector2{ size.x, 5 }, color),
	CollSouth(Vector2{ pos.x + size.x / 2 - 5, pos.y + size.y - 5 }, Vector2{ size.x, 5 }, color),
	CollWest(Vector2{ pos.x , pos.y + size.y / 2 - 5 }, Vector2{ 5, size.y }, color),
	CollEast(Vector2{ pos.x + size.x - 5, pos.y + size.y / 2 - 5 }, Vector2{ 5, size.y }, color)
{
	currFrame = 0;
	frameAcum = 0;
	rect = { pos.x, pos.y, size.x, size.y };
}

void Entity::Update() {}

void Entity::draw() {}

void Entity::HandleInput() {}

void Entity::UpdateTexture() {}

void Entity::UpdatePhysics()
{
	rect.width = size.x;
	rect.height = size.y;
	rect.x = position.x;
	rect.y = position.y;
	updateCollision();
}

void Entity::updateCollision()
{
	CollNorth.setX(position.x + size.x / 2 - CollNorth.getWidth() / 2);
	CollNorth.setY(position.y);

	CollSouth.setX(position.x + size.x / 2 - CollSouth.getWidth() / 2);
	CollSouth.setY(position.y + size.y - CollSouth.getHeight());

	CollEast.setX(position.x + size.x - CollEast.getWidth());
	CollEast.setY(position.y + size.y / 2 - CollEast.getHeight() / 2);

	CollWest.setX(position.x);
	CollWest.setY(position.y + size.y / 2 - CollWest.getHeight() / 2);
}

CollisionType Entity::CheckCollision(const Entity& entity) const {
	Rectangle rect = entity.getRect();
	if (CollNorth.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		return COLLISION_TYPE_NORTH;
	}
	if (CollSouth.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		return COLLISION_TYPE_SOUTH;
	}
	if (CollEast.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		return COLLISION_TYPE_EAST;
	}
	if (CollWest.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		return COLLISION_TYPE_WEST;
	}
	return COLLISION_TYPE_NONE;
}

bool Entity::isOnGround() const {
	return state == ON_GROUND;
}
void Entity::RunLeft() {

}
void Entity::RunRight() {

}
void Entity::Jumping() {

}
// Setter
void Entity::setPosition(Vector2 pos) {
	this->position = pos;
}
void Entity::setX(float x)
{
	this->position.x = x;
}
void Entity::setY(float y)
{
	this->position.y = y;
}
void Entity::setSize(Vector2 sz) {
	this->size = sz;
	rect.x = size.x;
	rect.y = size.y;
}
void Entity::setWidth(float width)
{
	this->size.x = width;
}
void Entity::setHeight(float height)
{
	this->size.y = height;
}
void Entity::setVel(Vector2 vel) {
	this->velocity = vel;
}
void Entity::setVelX(float velx)
{
	this->velocity.x = velx;
}
void Entity::setVelY(float vely)
{
	this->velocity.y = vely;
}
void Entity::setState(EntityState state) {
	this->state = state;
}
void Entity::setColor(Color color)
{
	this->color = color;
}
// Getter
Vector2& Entity::getPosition() {
	return position;
}
float Entity::getX() const
{
	return position.x;
}
float Entity::getY() const
{
	return position.y;
}
Vector2 Entity::getCenter() const
{
	return Vector2{ position.x + size.x / 2, position.y + size.y / 2 };
}
Vector2& Entity::getSize() {
	return size;
}
float Entity::getWidth() const
{
	return size.x;
}
float Entity::getHeight() const
{
	return size.y;
}
Vector2& Entity::getVelocity() {
	return velocity;
}
float Entity::getVelX() const
{
	return velocity.x;
}
float Entity::getVelY() const
{
	return velocity.y;
}
EntityState Entity::getState() const {
	return state;
}
Direction Entity::getDir() const {
	return direction;
}
// frame control
int Entity::getMaxFrame() const {
	return maxFrame;
}
int Entity::getCurrFrame() const {
	return currFrame;
}
float Entity::getFrameTime() const {
	return frameTime;
}
float Entity::getFrameAcum() const {
	return frameAcum;
}
Texture2D Entity::getCurrTexture() const {
	return texture;
}
std::string Entity::getName() const {
	return Entity_name;
}

Rectangle Entity::getRect() const
{
	return Rectangle{ position.x, position.y, size.x, size.y };
}

Color& Entity::getColor()
{
	return color;
}