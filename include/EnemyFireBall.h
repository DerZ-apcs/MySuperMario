#ifndef ENEMYFIREBALL_H
#define ENEMYFIREBALL_H
#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Entity.h"

class EnemyFireBall : public Entity {
private:
    float timeSpan;
    float timeSpanAcum;
    static const float maxDistance;
    static const float FB_SpeedX;
    bool isDestroyed;
public:
    EnemyFireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan);
    ~EnemyFireBall();
    void Update() override;
    void draw() override;
    void updateCollision() override;
    void UpdateTexture() override;
    bool isMaxDistance() const;
    void HandleTileCollision(const Tile tile, CollisionType Colltype);
    void destroy();
    bool IsDestroyed() { return isDestroyed; }
};

#endif