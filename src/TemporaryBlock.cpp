#include "../include/TemporaryBlock.h"

TemporaryBlock::TemporaryBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
	this->lifeTime = 5.0f; // Default lifetime of 5 seconds
	this->isDying = false;
	this->dead = false;
	this->texture = RESOURCE_MANAGER.getTexture("TILE_0");
}

void TemporaryBlock::Update() 
{
	if (isDying && !dead) {
		lifeTime -= GetFrameTime();
		if (lifeTime <= 0) {
			collisionAvailable = false; // Disable collision when dying
			dead = true;
			isDying = false;
		}
	}
}


void TemporaryBlock::setDying(bool dying)
{
	if (dead || isDying) return; // If already dead, ignore further dying requests
	this->isDying = dying;
	if (dying) {
		lifeTime = 5.0f; // Reset lifetime when starting to die
	}
}

void TemporaryBlock::draw() 
{
	if (!dead) {
		if (isDying && lifeTime <= 1.0f) {
			// Fade out effect
			Color fadeColor = Fade(WHITE, lifeTime);
			DrawTexture(texture, position.x, position.y, fadeColor);
			if (SETTING.isSoundEnabled()) {
				RESOURCE_MANAGER.playSound("lost_suit.wav");
			}
		}
		else {
			// Normal draw
			DrawTexture(texture, position.x, position.y, WHITE);
		}
	}
}

void TemporaryBlock::loadEntity(const json& j)
{

}

void TemporaryBlock::saveEntity(json& j) const
{
}

BLOCK_TYPE TemporaryBlock::getBlockType() const
{
	return TEMPBLOCK;
}

