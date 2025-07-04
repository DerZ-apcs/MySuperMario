#ifndef QUESTION_H
#define QUESTION_H

#include <raylib.h>
#include "../include/Tile.h"

class QuestionBlock : public Tile {
private:
	bool isActive;

public:
	QuestionBlock(Vector2 pos);
	~QuestionBlock() = default;

	bool getActive() const;	
	void setActive(bool active);

	void Update() override;
	void UpdateTexture() override;
	void draw() override;

};

#endif // ! QUESTION_H
