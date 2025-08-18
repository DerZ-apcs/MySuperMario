#ifndef PETEYPIRANHA_H
#define PETEYPIRANHA_H

#include "Boss.h"
#include "Character.h" // Để tham chiếu đến người chơi (target)
#include <vector>
#include "raylib.h"

class SporeCloud;
// Các trạng thái hành vi của Petey Piranha
enum class PeteyPiranhaState {
    WALKING,        // Đi bộ qua lại
    VULNERABLE,     // Trạng thái yếu, có thể bị tấn công sau khi lao xuống
    SHOOTING,       // Bắn đạn lửa
    HURT,           // Bị dính sát thương
    BURROW_DOWN,    // Giai đoạn đang đào xuống đất
    HIDDEN,         // Giai đoạn ẩn và di chuyển dưới lòng đất
    EMERGE,          // Giai đoạn trồi lên khỏi mặt đất

};

class PeteyPiranha : public Boss {
private:
    PeteyPiranhaState currentState;
    Character* target; // Mục tiêu (người chơi)

    float walkSpeed;
    float jumpPower;
    float groundPoundSpeed;

    // Timer điều khiển hành vi
    float actionTimer;     // Hẹn giờ cho hành động tiếp theo
    float statePhaseTimer; // Hẹn giờ cho một pha trong trạng thái hiện tại

    // Các phương thức cập nhật cho từng trạng thái
    void updateWalking();
    void updateVulnerable();
    void updateShooting();
    void updateHurt();
    void updateBurrowDown();
    void updateHidden();
    void updateEmerge();

    void enterState(PeteyPiranhaState newState);
    std::vector<Texture2D> walkLeftTextures;
    std::vector<Texture2D> walkRightTextures;
    Texture2D hurtTexture;
    Texture2D vulnerableTexture;
    int currentFrame;
    float frameTimer;
    float frameDuration;

    void loadAnimations();
    void shootFireball(); // Hành động bắn đạn
    Vector2 targetPosition; // Vị trí mục tiêu để trồi lên

public:
    PeteyPiranha(Vector2 pos);
    PeteyPiranha(Vector2 pos, Character* player);
    virtual ~PeteyPiranha() = default;

    void updateBehavior() override;
    void onDeath() override;
    void onHit() override; // Được gọi khi nhận sát thương nhưng chưa chết
    float getScores() const override;

    void stomped() override; // Xử lý khi người chơi dẫm lên
    void CollisionWithFireball(FireBall* fireball) override; // Xử lý va chạm với đạn của người chơi
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // PETEYPIRANHA_H