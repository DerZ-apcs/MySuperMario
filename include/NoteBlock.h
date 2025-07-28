#ifndef NOTE_BLOCK_H
#define NOTE_BLOCK_H

#include "../include/Blocks.h" 

class NoteBlock : public Blocks {
private:
	BOUNCE_DIRECTION bounce_dir;

	float bounceOffset = 0.0f;
	static const float bounceSpeed;    // How fast it moves during bounce
	static const float bounceMax;       // How far it moves (in pixels)

public:
	NoteBlock(Vector2 pos = {0, 0}, Vector2 size = {32, 32});
	~NoteBlock() = default;

	BOUNCE_DIRECTION getBounceDir() const;
	void setBounceDir(BOUNCE_DIRECTION dir);

	BLOCK_TYPE getBlockType() const override;

	void Update() override;
	void UpdateTexture() override;
	void draw() override;
};

#endif // !NOTE_BLOCK_H