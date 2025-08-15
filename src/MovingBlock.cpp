#include "../include/MovingBlock.h"

MovingBlock::MovingBlock(Vector2 pos, Vector2 size):
	Blocks(pos, size)
{
    texture = RESOURCE_MANAGER.getTexture("TILE_1");
    // Initialize bounds relative to initial position (e.g., ±100 units)
    boundLeft = pos.x - 100.0f;
    boundRight = pos.x + 100.0f;
    boundTop = pos.y - 100.0f;
    boundBottom = pos.y + 100.0f;
    // Default velocity for horizontal movement (Mario-style platform)
    velocity = { 50.0f, 50.0f }; // Move right initially, no vertical movement
}

BLOCK_TYPE MovingBlock::getBlockType() const
{
	return MOVINGBLOCK;
}

void MovingBlock::draw()
{
    // Draw the texture at the block's current position (inherited from Blocks)
    if (texture.id > 0) { // Check if texture is valid
        DrawTextureV(texture, position, WHITE);
    }
    if (SETTING.getDebugMode()) 
		DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, RED); // Draw block bounds for debugging
}

void MovingBlock::setBounds(float left, float right, float top, float bottom)
{
    boundLeft = left;
    boundRight = right;
    boundTop = top;
    boundBottom = bottom;
}

Vector2 MovingBlock::getVelocity() const
{
	return velocity;
}

void MovingBlock::setVelocity(Vector2 newVelocity)
{
    this->velocity = newVelocity;
}

void MovingBlock::Update()
{
    // Update position based on velocity and frame time for smooth movement
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    // Handle horizontal bounds: reverse velocity if block hits left or right boundary
    if (position.x <= boundLeft) {
        position.x = boundLeft; // Clamp to boundary
        velocity.x = -velocity.x; // Reverse direction
    }
    else if (position.x + size.x >= boundRight) {
        position.x = boundRight - size.x; // Clamp to boundary
        velocity.x = -velocity.x; // Reverse direction
    }

    // Handle vertical bounds: reverse velocity if block hits top or bottom boundary
    if (position.y <= boundTop) {
        position.y = boundTop; // Clamp to boundary
        velocity.y = -velocity.y; // Reverse direction
    }
    else if (position.y + size.y >= boundBottom) {
        position.y = boundBottom - size.y; // Clamp to boundary
        velocity.y = -velocity.y; // Reverse direction
    }
}

void MovingBlock::loadEntity(const json& j)
{
}

void MovingBlock::saveEntity(json& j) const
{
}
