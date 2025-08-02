#ifndef MARISA_H
#define MARISA_H

#include "../include/Character.h"
#include "../include/FireBall.h"

class Marisa : public Character {
private:
	const float maxspeedX = 650;
	const float maxSpeedY = 550;
public:
	Marisa();
	Marisa(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Marisa();
	CharacterType getCharacterType() const override;
	void draw() override;
	void reset() override;
	void UpdateTexture() override;
	//void updateCollision() override;
};
#endif