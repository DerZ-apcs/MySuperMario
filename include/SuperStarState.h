#ifndef SUPERSTARSTATE_H
#define SUPERSTARSTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class SuperStarState : public State {
    friend class Character;
public:
    SuperStarState(Character* character = nullptr);
    ~SuperStarState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif