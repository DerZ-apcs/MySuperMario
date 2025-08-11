#ifndef SPORECLOUD_H
#define SPORECLOUD_H

#include "Effect.h"
#include "Character.h"
#include "GameEngine.h"

constexpr float SPORE_CLOUD_LIFESPAN = 8.0f;

class SporeCloud : public Effect {
private:
    float dropTimer;
    Character* target;
    bool isFiringLeft; 
    float faceDirection;

public:
    SporeCloud(Vector2 pos, Character* target);
    virtual ~SporeCloud() = default;
    void Update() override;
    void draw() override;
    EntityType getEntityType() const override;
};

#endif // SPORECLOUD_H