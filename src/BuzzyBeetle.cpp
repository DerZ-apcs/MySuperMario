#include "../include/BuzzyBeetle.h"
#include "../include/ResourceManager.h"

BuzzyBeetle::BuzzyBeetle(Vector2 pos, Texture2D texture)
    : Koopa(pos, texture) {
    // Default Koopa constructor sets up walking, shell and revive logic
}

void BuzzyBeetle::UpdateTexture() {
    if (state == STATE_SHELL || state == STATE_IS_DYING) {
        if (state == STATE_SHELL && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 3;
                frameAcum = 0;
            }
            texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_Shell_2");
        }
        return;
    }
    if (state == ON_GROUND) {
        frameAcum += GetFrameTime();
        if (frameAcum > frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0;
        }
        if (direction == LEFT) {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_LEFT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_LEFT_1");
            }
        }
        else {
            if (currFrame == 0) {
                texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_RIGHT_0");
            }
            else {
                texture = Singleton<ResourceManager>::getInstance().getTexture("BuzzyBeetle_RIGHT_1");
            }
        }
    }
}

void BuzzyBeetle::CollisionWithFireball(FireBall& fireball) {
    // Buzzy Beetles are immune to fireballs; override to do nothing
}