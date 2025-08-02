#ifndef TOAD_H
#define TOAD_H
#include "../include/Character.h"
#include "../include/FireBall.h"

class Toad : public Character {
private:
	const float maxSpeedX = 600;
	const float maxSpeedY = 550;
public:
	Toad();
	Toad(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Toad();
	CharacterType getCharacterType() const override;
	void draw() override;
	void reset() override;
};
#endif