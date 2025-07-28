#ifndef ROTATING_BLOCK_H
#define ROTATING_BLOCK_H

#include <raylib.h>
#include "../include/Blocks.h" 

class RotatingBlock : public Blocks {
private:
	bool isActive;

	float rotatingTime;
	static const float ROTATION_PERIOD;

public:
	RotatingBlock(Vector2 pos = {0, 0}, Vector2 size = {32, 32});
	~RotatingBlock() = default;

	bool getActive() const;
	void setActive(bool active);
	void Activate();

	BLOCK_TYPE getBlockType() const override;

	void Update() override;
	void UpdateTexture() override;
	void draw() override;
};

#endif // !ROTATING_BLOCK_H