#ifndef SPOREDROPLET_H
#define SPOREDROPLET_H

#include "Effect.h"
#include "Character.h"
#include "GameEngine.h"

class SporeDroplet : public Effect {
public:
    SporeDroplet(Vector2 pos);
    virtual ~SporeDroplet() = default;

    void Update() override;
    void draw() override;
    EntityType getEntityType() const override;
};

#endif // SPOREDROPLET_H