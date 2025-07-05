#ifndef FIRESTATE_H
#define FIRESTATE_H

#include "../include/State.h" 
#include "../include/Character.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"

class FireState : public State {
    friend class Character;
public:
    FireState(Character* character = nullptr);
    ~FireState() = default;

    void UpdateTexture() override;
    STATE getState() const override;
};

#endif