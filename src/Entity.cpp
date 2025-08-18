#include "../include/Entity.h"
#include "../include/GameEngine.h"

Entity::Entity():
	Entity(Vector2{0, 0}, Vector2{0, 0}, Vector2{0, 0}, RIGHT, IDLING, {0}, 0.1f, 0, BLACK)
{}
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex, std::string name):
	Entity(pos, sz, vel, dir, state, tex, 0.1, 0, BLACK)
{

}
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state,
	Texture2D tex, float FrameTime, int MaxFrame, Color color):
	position(pos), size(sz), velocity(vel), direction(dir), state(state), texture(tex),
	frameTime(FrameTime), maxFrame(MaxFrame), frameAcum(0), currFrame(0), color(color),
	dead(false)
{
	CollNorth.setColor(color);
	CollEast.setColor(color);
	CollSouth.setColor(color);
	CollWest.setColor(color);
}
// main
Entity::Entity(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, float FrameTime, int MaxFrame, Color color):
	position(pos), size(sz), velocity(vel), direction(dir), state(state), frameTime(FrameTime), maxFrame(MaxFrame), color(color),
	CollNorth(Vector2{ pos.x + size.x / 2 - 5, pos.y }, Vector2{ size.x, 5 }, color),
	CollSouth(Vector2{ pos.x + size.x / 2 - 5, pos.y + size.y - 5 }, Vector2{ size.x, 5 }, color),
	CollWest(Vector2{ pos.x , pos.y + size.y / 2 - 5 }, Vector2{ 5, size.y }, color),
	CollEast(Vector2{ pos.x + size.x - 5, pos.y + size.y / 2 - 5 }, Vector2{ 5, size.y }, color),
	collisionAvailable(true),
	gravityAvailable(true),
	isjumping(false),
	dead(false)
{
	currFrame = 0;
	frameAcum = 0;
	rect = { pos.x, pos.y, size.x, size.y };
}

void Entity::Update() {
	if (isDead()) return;
	if (globalGameEngine) {
		Vector2 bound = globalGameEngine->getBound();
		if (this->getX() > bound.x || this->getY() > bound.y)
			setEntityDead();
	}
}
void Entity::draw() {

}
void Entity::HandleInput() {

}

void Entity::updateCollision() // update 4 rects in 4 sides of entity
{
	// update the hitbox collision 

	CollNorth.setSize({ size.x / 2, 5 });
	CollSouth.setSize({ size.x / 2, 5 });
	CollWest.setSize({ 5, size.y - 5 });
	CollEast.setSize({ 5, size.y - 5 });

	CollNorth.setX(position.x + size.x / 2 - CollNorth.getWidth() / 2);
	CollNorth.setY(position.y);
	
	CollSouth.setX(position.x + size.x / 2 - CollSouth.getWidth() / 2);
	CollSouth.setY(position.y + size.y - CollSouth.getHeight());
	
	CollEast.setX(position.x + size.x  - CollEast.getWidth() );
	CollEast.setY(position.y + size.y / 2 - CollEast.getHeight() / 2);

	CollWest.setX(position.x);
	CollWest.setY(position.y + size.y / 2 - CollWest.getHeight() / 2);
	//cout << size.x << " " << size.y << endl;
}

void Entity::UpdateTexture()
{
}

CollisionType Entity::CheckCollision(const Entity& entity) const
{
	Rectangle rect = entity.getRect();
	if (CollNorth.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		//entity->setColor(CollNorth.getColor());
		return COLLISION_TYPE_NORTH;
	}
	if (CollSouth.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		//entity->setColor(CollSouth.getColor());
		return COLLISION_TYPE_SOUTH;
	}
	if (CollEast.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		//entity->setColor(CollEast.getColor());
		return COLLISION_TYPE_EAST;
	}
	if (CollWest.checkCollision(rect) == COLLISION_TYPE_COLLIDED) {
		//entity->setColor(CollWest.getColor());
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
void Entity::setTexture(Texture2D tex)
{
	this->texture = tex;
}
bool Entity::isDead() const
{
	return dead;
}
void Entity::setEntityDead()
{
	this->dead = true;
}

void Entity::setJumping(bool value)
{
	isjumping = value;
}

void Entity::setDirection(Direction dir)
{
	this->direction = dir;
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

float Entity::getCenterX() const {
	return position.x + size.x / 2.f;
}

float Entity::getCenterY() const {
	return position.y + size.y / 2.f;
}

float Entity::getBottom() const {
	return position.y + size.y;
}

float Entity::getLeft() const {
	return position.x;
}

float Entity::getRight() const {
	return position.x + size.x;
}

float Entity::getTop() const {
	return position.y;
}

void Entity::setCollisionAvailable(bool collisionAvailable)
{
	this->collisionAvailable = collisionAvailable;
}

void Entity::setGravityAvailable(bool gravityAvailable)
{
	this->gravityAvailable = gravityAvailable;
}

bool Entity::getCollisionAvailable()
{
	return collisionAvailable;
}

bool Entity::getGravityAvailable()
{
	return gravityAvailable;
}

void Entity::saveEntity(json& j) const {
	j["pos"] = { position.x, position.y };
	j["size"] = { size.x, size.y };
	j["vel"] = { 0.f, 0.f };
	j["direction"] = static_cast<int>(direction);
	j["EntityState"] = static_cast<int>(state);

	j["maxFrame"] = maxFrame;
	j["currFrame"] = currFrame;
	j["frameTime"] = frameTime;
	j["frameAcum"] = 0;

	// Note: Texture2D is not serializable directly. Save the path instead.

	j["isJumping"] = isjumping;
	j["gravityAvailable"] = gravityAvailable;
	j["collisionAvailable"] = collisionAvailable;
	j["dead"] = dead;

	j["type"] = static_cast<int>(getEntityType()); // used for reconstruction
}


void Entity::loadEntity(const json& j) 
{
	position = { j["pos"][0], j["pos"][1] };
	size = { j["size"][0], j["size"][1] };
	velocity = { j["vel"][0], j["vel"][1] };
	direction = static_cast<Direction>(j["direction"].get<int>());
	state = static_cast<EntityState>(j["EntityState"].get<int>());

	maxFrame = j["maxFrame"];
	currFrame = j["currFrame"];
	frameTime = j["frameTime"];
	frameAcum = 0; // frameAcum is reset to 0 when loading

	isjumping = j["isJumping"];
	gravityAvailable = j["gravityAvailable"];
	collisionAvailable = j["collisionAvailable"];
	dead = j["dead"];
}

