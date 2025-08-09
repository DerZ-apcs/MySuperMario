#ifndef SPORECLOUD_H
#define SPORECLOUD_H

#include "Effect.h"
#include "Character.h"
#include "GameEngine.h"

class SporeCloud : public Effect {
private:
    float damageCooldown;      // Hẹn giờ giữa các lần gây sát thương

public:
    // Constructor: Khởi tạo đám mây tại một vị trí
    SporeCloud(Vector2 pos);

    // Destructor
    virtual ~SporeCloud() = default;

    // Cập nhật logic của đám mây (đếm ngược thời gian, kiểm tra va chạm)
    void Update() override;

    // Vẽ đám mây lên màn hình
    void draw() override;

    // Trả về loại thực thể
    EntityType getEntityType() const override;
};

#endif // SPORECLOUD_H