#ifndef STAR_H
#define STAR_H

#include "../include/PowerItem.h"

class Star : public PowerItem {
private:
    static constexpr float SPEED = 70.f;
    StarType type;
public:
    Star(StarType type = YELLOW_STAR, Vector2 position = { 0.f, 0.f }, Vector2 sz = { 32, 32 }, Direction direction = RIGHT);

    float getPoint() const override;
    const StarType& getStarType() const;
    //void Update() override;
    ITEM_TYPE getItemType() const override;
};

#endif // STAR_H