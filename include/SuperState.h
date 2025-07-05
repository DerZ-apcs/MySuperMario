#ifndef SUPERSTATE_H
#define SUPERSTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class SuperState : public State {
    friend class Character;
public:
    SuperState(Character* character = nullptr);
    ~SuperState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif