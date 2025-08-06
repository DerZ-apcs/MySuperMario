#ifndef BOOMBOOM_H
#define BOOMBOOM_H

#include "Boss.h"
#include "Character.h" // Cần để tham chiếu đến người chơi

enum class BoomBoomState {
    WALKING,    // Đi bộ qua lại
    JUMP_ASCEND,  // Cải tiến: Pha bay lên
    JUMP_APEX,    // Cải tiến: Pha dừng trên không
    JUMP_DESCEND, // Cải tiến: Pha lao xuống
    SPINNING,   // Quay tròn, chuẩn bị lao tới
    CHARGING,   // Lao về phía người chơi
    STUNNED,    // Bị choáng sau khi lao hoặc bị tấn công
    HIDDEN      // Trạng thái ẩn mình sau khi bị dẫm lên
};

class BoomBoom : public Boss {
private:
    BoomBoomState currentState;
    Character* target; 

    float walkSpeed;
    float chargeSpeed;
    float jumpPower;
    bool isEnraged;
    float actionTimer;     
    float statePhaseTimer;  

    void updateWalking();
    void updateJumpAscend();
    void updateJumpApex();
    void updateJumpDescend();
    void updateSpinning();
    void updateCharging();
    void updateStunned();
    void updateHidden();

    void enterState(BoomBoomState newState);

    std::vector<Texture2D> walkLeftTextures;
    std::vector<Texture2D> walkRightTextures;
    int currentFrame;
    float frameTimer;
    float frameDuration; 

    void loadAnimations();

public:
    BoomBoom(Vector2 pos, Character* player);
    virtual ~BoomBoom() = default;

    void updateBehavior() override;
    void onDeath() override;
    void onHit() override;
    float getScores() const override;

    void stomped() override; 
    void CollisionWithFireball(FireBall* fireball) override; 
};

#endif // BOOMBOOM_H
