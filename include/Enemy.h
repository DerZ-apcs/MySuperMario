#ifndef ENEMY_H
#define ENEMY_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include <random>
#include <list>

class Character;
class FireBall;
static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

// Score
const int SCORE_STOMP_GOOMBA = 100;
const int SCORE_STOMP_KOOPA = 100;
const int SCORE_STOMP_SPINY = 100;
const int SCORE_KICK_KOOPA = 200;
const int SCORE_STOMP_BULLET = 200;
const int SCORE_STOMP_REX = 200;
const int SCORE_STOMP_MUNCHER = 200;

// Time
const float ENEMY_DEATH_TIMER_DEFAULT = 0.3f;
const float ENEMY_DEATH_TIMER_LONG = 0.5f;
const float KOOPA_REVIVE_TIME = 5.0f;
const float KOOPA_REVIVE_WARNING_TIME = 4.0f;
const float FLYINGGOOMBA_JUMP_INTERVAL = 1.0f;
// Speed
const float MARIO_BOUNCE_VELOCITY = -300.0f;
const float GOOMBA_SPEED = 100.0f;
const float FLYINGGOOMBA_SPEED = 100.0f;
const float FLYINGGOOMBA_JUMP_VELOCITY = -600.0f;
const float KOOPA_SPEED = 80.0f;
const float KOOPA_SHELL_SPEED = 300.0f;
const float BULLET_SPEED = 300.0f;
const float REX_SPEED = 120.0f;
const float REX_COMPRESSED_SPEED = 180.0f;

// Base class for enemies, inheriting from Entity
class Enemy : public Entity {
protected:
    float deathTimer; // Timer for death animation
    float squashScale; // Scale for squash effect when dying 
    bool isFlipped;
    bool isKicked;
    float collisionTimer;
public:
    Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction direction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color);
    virtual ~Enemy();
    virtual void stomped(); // Handle collision with Mario
    //virtual void CollisionWithEnemy(Enemy& enemy, CollisionType collType); // Handle collision with other enemies
    virtual void CollisionWithFireball(FireBall* fireball);
    virtual ENEMY_TYPE getEnemyType() const = 0;
    EntityType getEntityType() const override;
    bool isDying(); // Check if enemy is dying or marked for removal
    bool isReadyForRemoval();
    void Update() override;
    void draw() override;
    void updateSquashEffect();
    void updateCollision() override;
    virtual void kicked(Direction direction);
    bool getIsKicked() const;
    void setIsKicked(bool isKicked);
    virtual void UpdateTexture(); // Update enemy texture based on state
    virtual void attacked(Direction direction = RIGHT);
    virtual float getScores() const = 0;
    void setCollisionTimer(float time);
    void setDeathTimer(float time);
};

#endif