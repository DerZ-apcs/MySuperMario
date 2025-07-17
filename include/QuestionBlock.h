#ifndef QUESTION_H
#define QUESTION_H

#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Blocks.h"
#include "../include/Item.h"
#include "../include/PowerItem.h"
#include "../include/Mushroom.h"
#include "../include/Star.h"
#include "../include/Flower.h"

class QuestionBlock : public Blocks {
private:
	bool isActive;
	ITEM_TYPE heldPowerUp;

public:
	QuestionBlock(Vector2 pos, ITEM_TYPE type);
	~QuestionBlock() = default;

	bool getActive() const;	
	void setActive(bool active);
	void Activate();

	BLOCK_TYPE getBlockType() const override;

	void Update() override;
	void UpdateTexture() override;
	void draw() override;

};

#endif // ! QUESTION_H
