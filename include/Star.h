#ifndef STAR_H
#define STAR_H

#include "../include/Item.h"

class Star : public Item {
private:
    static constexpr int POINT = 1000;
    static constexpr float SPEED = 70.f;

    StarType type;

    static constexpr float APPEAR_SPEED = 16.f;
public:
    Star(StarType type = YELLOW_STAR, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);

    const StarType& getStarType() const;
    void Update() override;
    void draw() override;
    void updateCollision() override;
    void UpdateTexture() override;
    void HandleTileCollision(const Tile tile, CollisionType Colltype);
    ITEM_TYPE getItemType() const override;
};

#endif // STAR_H