#ifndef BOOMBOOM_H
#define BOOMBOOM_H

#include "Boss.h"
#include "Character.h" // Cần để tham chiếu đến người chơi

enum class BoomBoomState {
    WALKING,    // Đi bộ qua lại
    JUMPING,    // Nhảy lên cao và tấn công
    SPINNING,   // Quay tròn, chuẩn bị lao tới
    CHARGING,   // Lao về phía người chơi
    STUNNED,    // Bị choáng sau khi lao hoặc bị tấn công
    HIDDEN      // Trạng thái ẩn mình sau khi bị dẫm lên
};

class BoomBoom : public Boss {
private:
    BoomBoomState currentState;
    Character* target; // Tham chiếu đến người chơi để xác định vị trí

    // Thuộc tính di chuyển và tấn công
    float walkSpeed;
    float chargeSpeed;
    float jumpPower;

    // Timer để điều khiển các trạng thái và hành động
    float actionTimer;      // Timer để quyết định hành động tiếp theo
    float statePhaseTimer;  // Timer cho các giai đoạn trong một trạng thái (ví dụ: thời gian choáng)

    // Hàm riêng để xử lý logic cho từng trạng thái
    void updateWalking();
    void updateJumping();
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
