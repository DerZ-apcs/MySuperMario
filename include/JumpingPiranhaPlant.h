// JumpingPiranhaPlant.h
#ifndef JUMPINGPIRANHAPLANT_H
#define JUMPINGPIRANHAPLANT_H

#include "../include/PiranhaPlant.h"

class JumpingPiranhaPlant : public PiranhaPlant {
private:
    float animTimer;
    static const float ANIM_INTERVAL;     // thời gian 1 chu kỳ lên–xuống
    static const float JUMP_HEIGHT;
    void UpdateTexture();
public:
    JumpingPiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario);
    void Update() override;

    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
};

#endif // JUMPINGPIRANHAPLANT_H
