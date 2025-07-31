#ifndef BOOMBOOM_H
#define BOOMBOOM_H

#include "Boss.h"
#include "CollisionInfo.h"

enum class BoomBoomState { IDLE, PREPARE_SMASH, SMASH, ROLL, STUN, DEAD };

class BoomBoom : public Boss {
private:
    BoomBoomState state;

    // Timing constants
    static constexpr float PREPARE_TIME = 0.5f;
    static constexpr float SMASH_DURATION = 0.3f;
    static constexpr float ROLL_DURATION = 1.2f;
    static constexpr float STUN_DURATION = 1.0f;

    // Movement constants
    static constexpr float ROLL_SPEED = 200.0f;
    static constexpr float SMASH_VELOCITY_Y = -600.0f;

    void changeState(BoomBoomState newState);
    void performSmash();
    void performRoll();

public:
    BoomBoom(Vector2 pos, Texture2D texture);
    void updateBehavior() override;
    void onHit() override;
    void onDeath() override;
    void UpdateTexture() override;
	float getScores() const override { return 1000.0f; } 
};

#endif // BOOMBOOM_H
