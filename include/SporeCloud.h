#ifndef SPORECLOUD_H
#define SPORECLOUD_H

#include "Effect.h"
#include "Character.h"
#include "GameEngine.h"

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