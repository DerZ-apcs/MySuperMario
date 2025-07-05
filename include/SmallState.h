#ifndef SMALLSTATE_H
#define SMALLSTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class NormalState : public State {
    friend class Character;
public:
    NormalState(Character* character = nullptr);
    ~NormalState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif