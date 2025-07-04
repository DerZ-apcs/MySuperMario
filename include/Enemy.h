#ifndef ENEMY_H
#define ENEMY_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include "../include/Tile.h"
#include <raymath.h>

// Điểm số
const int SCORE_STOMP_GOOMBA = 100;
const int SCORE_STOMP_KOOPA = 100;
const int SCORE_KICK_KOOPA = 200;
const int SCORE_STOMP_BULLET = 200;

// Thời gian
const float ENEMY_DEATH_TIMER_DEFAULT = 0.3f;
const float ENEMY_DEATH_TIMER_LONG = 0.5f;
const float KOOPA_REVIVE_TIME = 5.0f;
const float KOOPA_REVIVE_WARNING_TIME = 4.0f;
const float FLYINGGOOMBA_JUMP_INTERVAL = 1.0f;

// Tốc độ
const float MARIO_BOUNCE_VELOCITY = -300.0f;
const float GOOMBA_SPEED = 100.0f;
const float FLYINGGOOMBA_SPEED = 100.0f;
const float FLYINGGOOMBA_JUMP_VELOCITY = -500.0f;
const float KOOPA_SPEED = 80.0f;
const float KOOPA_SHELL_SPEED = 300.0f;
const float BULLET_SPEED = 300.0f;

// Base class for enemies, inheriting from Entity
class Enemy : public Entity {
protected:
    float deathTimer; // Timer for death animation
    float squashScale; // Scale for squash effect when dying
    void updateSquashEffect(); // Update squash effect during death animation
    bool isDead; // Flag to mark enemy for removal
    bool isFlipped;
public:
    Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction direction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color);
    virtual ~Enemy();
    virtual void CollisionWithCharacter(Mario& mario, CollisionType collType); // Handle collision with Mario
    virtual void CollisionWithEnemy(Enemy& enemy, CollisionType collType); // Handle collision with other enemies
    bool isDying(); // Check if enemy is dying or marked for removal
    bool isReadyForRemoval();
    void Update() override;
    void draw() override;
    void updateCollision() override;
    virtual void UpdateTexture(); // Update enemy texture based on state
    virtual void HandleTileCollision(const Tile& tile, CollisionType collType); // Handle collision with tiles
};

#endif