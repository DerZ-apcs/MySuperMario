#ifndef MARIO_H
#define MARIO_H
#include <raylib.h>
#include "../include/Character.h"
#include "../include/FireBall.h"
#include "../include/Tile.h"
#include <string>
#include <list>

class Mario: public Character {
private:
	const float maxspeedX = 550;
	const float maxSpeedY = 550;
public:
	Mario();
	Mario(Vector2 nposition, Vector2 nsize, CharacterState type);
	~Mario();
	CharacterType getCharacterType() const override;
	void RunLeft() override;
	void RunRight() override;
	void Jumping() override;
	void UpdateTexture() override;
	void reset() override;
};
#endif