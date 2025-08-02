#ifndef MOON_H
#define MOON_H

#include "../include/PowerItem.h"

class Moon : public PowerItem {
private:
    const float speedX = 200.f;
public:
    Moon(MoonType moonType = NORMAL_MOON, Vector2 position = { 0.f, 0.f }, Direction direction = RIGHT);

    float getPoint() const override;
    ITEM_TYPE getItemType() const override;
};
#endif