#include "../include/NoteBlock.h"
#include "../include/GameEngine.h"

const float NoteBlock::bounceSpeed = 120.0f; // Speed of the bounce in pixels per second
const float NoteBlock::bounceMax = 24.0f; // Maximum bounce height in pixels

//-----------------

NoteBlock::NoteBlock(Vector2 pos) :
	Blocks(pos, { 32, 32 }, "NOTE_0"), bounce_dir(NO_BOUNCE) {
	this->frameAcum = 0;
	this->currFrame = 0;
	this->frameTime = 0.2f;
	this->maxFrame = 4;
}

//-----------------

BOUNCE_DIRECTION NoteBlock::getBounceDir() const {
	return bounce_dir;
}

void NoteBlock::setBounceDir(BOUNCE_DIRECTION dir) {
	bounce_dir = dir;
}

BLOCK_TYPE NoteBlock::getBlockType() const {
	return NOTEBLOCK;
}

//-----------------

void NoteBlock::Update() {
    float dt = GetFrameTime();

    if (bounce_dir == BOUNCE_UP) {
        bounceOffset -= bounceSpeed * dt;
        if (bounceOffset <= -bounceMax) {
            bounceOffset = -bounceMax;
            bounce_dir = NO_BOUNCE; // End bounce
        }
    }
    else if (bounce_dir == BOUNCE_DOWN) {
        bounceOffset += bounceSpeed * dt;
        if (bounceOffset >= bounceMax) {
            bounceOffset = bounceMax;
            bounce_dir = NO_BOUNCE;
        }
    }
    else {
        // Return to original  
        if (bounceOffset < 0) {
            bounceOffset += bounceSpeed * dt;
            if (bounceOffset > 0) bounceOffset = 0;
        }
        else if (bounceOffset > 0) {
            bounceOffset -= bounceSpeed * dt;
            if (bounceOffset < 0) bounceOffset = 0;
        }
    }


	UpdateTexture();
}

void NoteBlock::UpdateTexture() {
	frameAcum += GetFrameTime();
	if (frameAcum >= frameTime) {
		frameAcum = 0;
		currFrame = (currFrame + 1) % maxFrame;

		std::string textureName = "NOTE_" + std::to_string(currFrame);
		texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
	}
}

void NoteBlock::draw() {
	DrawTexture(texture, position.x, position.y + bounceOffset, WHITE);
}