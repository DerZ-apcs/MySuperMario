// JumpingPiranhaPlant.h
#ifndef JUMPINGPIRANHAPLANT_H
#define JUMPINGPIRANHAPLANT_H

#include "../include/PiranhaPlant.h"

class JumpingPiranhaPlant : public PiranhaPlant {
private:
    float animTimer;
    static const float ANIM_INTERVAL;     // thời gian 1 chu kỳ lên–xuống
    static const float JUMP_HEIGHT;
    static constexpr const char* TEX_UP = "PiranhaPlant_JUMPING_1";
    static constexpr const char* TEX_DOWN = "PiranhaPlant_JUMPING_2";

    void UpdateTexture(bool isGoingUp);
public:
    JumpingPiranhaPlant(Vector2 pos, Texture2D texture);
    void Update() override;
    void stomped() override;
};

#endif // JUMPINGPIRANHAPLANT_H


