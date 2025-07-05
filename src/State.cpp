#include "../include/State.h"

State::State(Character* character) {
	this->character = character;
}

void State::setCharacter(Character* character)
{
	this->character = character;
}

Character* State::getCharacter() const
{
	return character;
}
