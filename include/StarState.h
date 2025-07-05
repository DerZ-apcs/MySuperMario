#ifndef STARSTATE_H
#define STARSTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class FireBall;

class StarState : public State {
    friend class Character;
public:
    StarState(Character* character = nullptr);
    ~StarState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif