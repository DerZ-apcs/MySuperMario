#include "../include/Muncher.h"
#include "../include/Mario.h"

Muncher::Muncher(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 32 }, { 0, 0 }, RIGHT, ON_GROUND, texture, 0.25f, 1, DARKGREEN) {
    velocity = { 0, 0 };
    this->texture = Singleton<ResourceManager>::getInstance().getTexture("Muncher_1");
}

void Muncher::Update() {
    UpdateTexture();
    Enemy::Update();
}

void Muncher::draw() {
    Enemy::draw();
}

void Muncher::UpdateTexture() {
    if (state == STATE_IS_DYING) return;

    frameAcum += GetFrameTime();
    if (frameAcum >= frameTime) {
        frameAcum -= frameTime;
        currFrame = (currFrame + 1) % (maxFrame + 1);
    }

    if (currFrame == 0) {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Muncher_0");
    }
    else {
        texture = Singleton<ResourceManager>::getInstance().getTexture("Muncher_1");
    }
}

void Muncher::CollisionWithCharacter(Mario& mario, CollisionType collType) {
    if (mario.getInvincibilityTimer() > 0) {
        return;
    }

    if (mario.getMarioState() == STATE_SUPER || mario.getMarioState() == STATE_FIRE_BALL) {
        mario.TransitionToSmall();
        mario.setInvincibilityTimer(1.0f); 
    }
    else {
        mario.setState(STATE_IS_DYING);
        Singleton<ResourceManager>::getInstance().playSound("MARIO_DIE");
    }
}

void Muncher::CollisionWithFireball(FireBall& fireball) {
    fireball.destroy();
}

void Muncher::HandleTileCollision(const Tile& tile, CollisionType collType) {
    if (collType == COLLISION_TYPE_SOUTH) {
        setY(tile.getY() - getHeight());
        velocity.y = 0;
        state = ON_GROUND;
    }
}