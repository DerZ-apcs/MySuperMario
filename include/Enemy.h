#ifndef ENEMY_H
#define ENEMY_H
#include "../include/Entity.h"
#include "../include/Mario.h"
#include "../include/Tile.h"

// Base class for enemies, inheriting from Entity
class Enemy : public Entity {
protected:
    float deathTimer; // Timer for death animation
    float squashScale; // Scale for squash effect when dying
    void updateSquashEffect(); // Update squash effect during death animation
    bool isDead; // Flag to mark enemy for removal
public:
    Enemy(Vector2 pos, Vector2 size, Vector2 vel, Direction direction, EntityState state, Texture2D texture, float frameTime, int maxFrame, Color color);
    virtual ~Enemy();
    virtual void CollisionWithCharacter(Mario& mario, CollisionType collType); // Handle collision with Mario
    virtual void CollisionWithEnemy(Enemy& enemy, CollisionType collType); // Handle collision with other enemies
    bool isDying(); // Check if enemy is dying or marked for removal
    void Update() override;
    void draw() override;
    void updateCollision() override;
    virtual void UpdateTexture(); // Update enemy texture based on state
    virtual void HandleTileCollision(const Tile& tile, CollisionType collType); // Handle collision with tiles
};

class Goomba : public Enemy {
public:
    Goomba(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
};

class FlyingGoomba : public Goomba {

};

class Koopa : public Enemy {
public:
    Koopa(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
private:
    float reviveTimer; // Timer for reviving from Shell state
};

#endif