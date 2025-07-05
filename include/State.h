#ifndef STATE_H
#define STATE_H

#include "../include/Global.h"

class Entity;
class Mario;
class Luigi;
class Character;
class Enemy;

// State: All states will implement this interface
class State {
private:
	Character* character;
public:
	State(Character* character = nullptr);
	virtual ~State() = default;
	virtual void UpdateTexture() = 0;
	virtual CharacterState getCharacterState() const = 0;
	virtual void setCharacter(Character* character = nullptr);
	virtual Character* getCharacter() const;
};