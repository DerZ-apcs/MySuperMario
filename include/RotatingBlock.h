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
	RotatingBlock(Vector2 pos);
	~RotatingBlock() = default;

	bool getActive() const;
	void setActive(bool active);
	void Activate();

	BLOCK_TYPE getBlockType() const override;

	void Update() override;
	void UpdateTexture() override;
	void draw() override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !ROTATING_BLOCK_H