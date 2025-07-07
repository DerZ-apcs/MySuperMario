#include "../include/Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction dirction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color)
{
}

Enemy::Enemy(Vector2 pos, Vector2 size)
{
}

EntityType Enemy::getEntityType() const
{
    return ENEMY;
}

Direction Enemy::getRandomDirection()
{
    return Direction();
}

void Enemy::setBoundary(Vector2 boundary)
{
}

const Vector2& Enemy::getBoundary() const
{
    return boundary;
}

void Enemy::stomped()
{
}

void Enemy::attacked(Direction direction)
{
}

void Enemy::CollisionWithFireBall(FireBall* fireball)
{
}

//void Enemy::CollisionWithCharacter()
//{
//}
//
//bool Enemy::isDying()
//{
//	return false;
//}

void Enemy::Update()
{
}

void Enemy::draw()
{
}

void Enemy::UpdateTexture()
{
}

void Enemy::updateCollision()
{
}
