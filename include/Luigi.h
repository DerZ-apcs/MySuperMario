#ifndef LUIGI_H
#define LUIGI_H
#include "../include/Character.h"
#include "../include/FireBall.h"
#include "../include/Tile.h"
#include <string>

class Luigi: public Character {
private:
	const float maxspeedX = 500;
	const float maxSpeedY = 600;
public:
	Luigi();
	Luigi(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Luigi();
	CharacterType getCharacterType() const override;
	void RunLeft() override;
	void RunRight() override;
	void Jumping() override;
	void UpdateTexture() override;
	void reset() override;
};
#endif