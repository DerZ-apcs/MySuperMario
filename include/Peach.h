#ifndef PEACH_H
#define PEACH_H

#include "../include/Character.h"
#include "../include/FireBall.h"

class Peach : public Character {
private:
	const float maxspeedX = 550;
	const float maxSpeedY = 550;
public:
	Peach();
	Peach(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Peach();
	CharacterType getCharacterType() const override;
	void draw() override;
	void reset() override;
	//void updateCollision() override;
};
#endif