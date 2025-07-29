// BuzzyBeetle.h
#ifndef BUZZYBEETLE_H
#define BUZZYBEETLE_H

#include "../include/Koopa.h"  
#include "../include/FireBall.h"

class BuzzyBeetle : public Koopa {
public:
    BuzzyBeetle(Vector2 pos, Texture2D texture);
    void UpdateTexture() override;
    void CollisionWithFireball(FireBall& fireball) override;
};

#endif // BUZZYBEETLE_H