#ifndef FIRESTARSTATE_H
#define FIRESTARSTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class FireStarState : public State {
    friend class Character;
public:
    FireStarState(Character* character = nullptr);
    ~FireStarState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif