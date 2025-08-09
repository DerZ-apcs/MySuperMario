#ifndef SPORECLOUD_H
#define SPORECLOUD_H

#include "Effect.h"
#include "Character.h"
#include "GameEngine.h"

constexpr float SPORE_CLOUD_LIFESPAN = 8.0f; // Tăng thời gian tồn tại của đám mây

class SporeCloud : public Effect {
private:
    float dropTimer;      // Hẹn giờ giữa các lần thả vật nguy hiểm
public:
    SporeCloud(Vector2 pos);
    virtual ~SporeCloud() = default;
    void Update() override;
    void draw() override;
    EntityType getEntityType() const override;
};

#endif // SPORECLOUD_H