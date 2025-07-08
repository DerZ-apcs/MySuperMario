#ifndef QUESTION_H
#define QUESTION_H

#include <raylib.h>
#include "../include/Tile.h"
#include "../include/PowerItem.h"
#include "../include/Mushroom.h"
#include "../include/Star.h"
#include "../include/Flower.h"

enum PowerUpType {
	POWERUP_MUSHROOM,
	POWERUP_FLOWER,
	POWERUP_STAR,
};

class QuestionBlock : public Tile {
private:
	bool isActive;
	PowerUpType holdedPowerUp;

public:
	QuestionBlock(Vector2 pos, PowerUpType type);
	~QuestionBlock() = default;

	bool getActive() const;	
	void setActive(bool active);
	void Activate(std::vector<PowerItem*>& PowerItems);

	void Update() override;
	void UpdateTexture() override;
	void draw() override;

};

#endif // ! QUESTION_H
