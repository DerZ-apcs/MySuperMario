#ifndef DRYBONES_H
#define DRYBONES_H

#include "../include/Enemy.h"

enum DryBonesState {
    DB_ALIVE,      // đi bộ bình thường
    DB_BROKEN,     // vỡ xương
    DB_REVIVING    // shake trước khi hồi sinh
};

class DryBones : public Enemy {
protected:
    DryBonesState dbState;
    float breakTimer;
    float reviveTimer;
    float shakeTimer;

    static constexpr float BREAK_DURATION = 0.5f;  // thời gian collapse
    static constexpr float REVIVE_DURATION = 1.5f;  // thời gian để shake rồi hồi sinh
    static constexpr float WALK_SPEED = 50.0f;

public:
    DryBones(Vector2 pos, Texture2D tex);
    void Update() override;
    void draw()   override;
    void CollisionWithCharacter(Mario& m, CollisionType ct) override;
    void HandleTileCollision(const Tile& t, CollisionType ct) override;
};

#endif