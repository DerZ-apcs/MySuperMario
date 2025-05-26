#include "../include/Entity.h"

Entity::Entity():
	Entity(Vector2{0, 0}, Vector2{0, 0}, Vector2{0, 0}, RIGHT, IDLING, texture, 0, 0)
{}
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex, std::string name):
	Entity(pos, sz, vel, dir, state, tex, 0.1, 0)
{

}
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state,
	Texture2D tex, float FrameTime, int MaxFrame):
	position(pos), size(sz), velocity(vel), direction(dir), state(state), texture(tex),
	frameTime(FrameTime), maxFrame(MaxFrame), frameAcum(0), currFrame(0)
{

}
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, float FrameTime, int MaxFrame):
	position(pos), size(sz), velocity(vel), direction(dir), state(state), frameTime(FrameTime), maxFrame(MaxFrame) { }

void Entity::Update() {

}
void Entity::draw() {

}
void Entity::HandleInput() {

}
void Entity::UpdateTexture() {

}
void Entity::updateCollision()
{
}

CollisionType Entity::CheckCollision(Entity* entity)
{
	return CollisionType();
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
void Entity::setSize(Vector2 sz) {
	this->size = sz;
}
void Entity::setVel(Vector2 vel) {
	this->velocity = vel;
}
void Entity::setState(EntityState state) {
	this->state = state;
}
// Getter
Vector2& Entity::getPosition() {
	return position;
}
float Entity::getX() const
{
	return 0.0f;
}
float Entity::getY() const
{
	return 0.0f;
}
Vector2 Entity::getCenter() const
{
	return Vector2();
}
Vector2& Entity::getSize() {
	return size;
}
float Entity::getWidth() const
{
	return 0.0f;
}
float Entity::getHeight() const
{
	return 0.0f;
}
Vector2& Entity::getVelocity() {
	return velocity;
}
float Entity::getVelX() const
{
	return 0.0f;
}
float Entity::getVelY() const
{
	return 0.0f;
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
	return Rectangle();
}

Color& Entity::getColor()
{
	// TODO: insert return statement here
}
