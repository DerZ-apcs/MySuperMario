// Spiny.cpp
#include "../include/Spiny.h"
#include "../include/GameEngine.h"

Spiny::Spiny(Vector2 pos, Texture2D texture)
    : Enemy(pos, { 32, 32 }, { 0,0 }, LEFT, ON_GROUND, texture, 0.2f, 1, WHITE)
{
	texture = RESOURCE_MANAGER.getTexture("Spiny_LEFT_0");
    updateCollision();
}

void Spiny::Update() {
    // Nếu đang die animation, dùng logic base để đếm timer và squash
    Entity::Update();
    if (isDying()) {
        Enemy::Update();
        return;
    }

    if (state == ON_GROUND) {
        velocity.x = (direction == LEFT ? -SPINY_SPEED : SPINY_SPEED);
	}
    Enemy::Update();
}

void Spiny::draw() {
    Enemy::draw();
}

void Spiny::UpdateTexture() {
    if (state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("Spiny_DEAD");
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % 2;
        frameAcum = 0;
    }
    std::string dir = (direction == LEFT ? "LEFT" : "RIGHT");
    texture = RESOURCE_MANAGER.getTexture("Spiny_" + dir + "_" + std::to_string(currFrame));
}

//void Spiny::CollisionWithCharacter(Mario& m, CollisionType ct) {
//    if (isDying()) return;
//    if (m.getInvincibilityTimer() <= 0) {
//        if (m.getMarioState() == STATE_SUPER || m.getMarioState() == STATE_FIRE_BALL) {
//            m.TransitionToSmall();
//            m.setInvincibilityTimer(2.0f);
//        }
//        else {
//            m.setState(STATE_IS_DYING);
//            RESOURCE_MANAGER.playSound("MARIO_DIE");
//        }
//    }
//}

//void Spiny::CollisionWithEnemy(Enemy& enemy, CollisionType ct) {
//    Koopa* k = dynamic_cast<Koopa*>(&enemy);
//    if (k && k->getState() == STATE_SHELL && k->getVelocity().x != 0
//        && (ct == COLLISION_TYPE_EAST || ct == COLLISION_TYPE_WEST)) {
//        state = STATE_IS_DYING;
//        deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
//        velocity.y = -200;
//        velocity.x = (rand() % 100) - 50;
//        updateCollision();
//    }
//}

//void Spiny::CollisionWithFireball(FireBall& fb) {
//    if (isDying()) return;
//    state = STATE_IS_DYING;
//    deathTimer = ENEMY_DEATH_TIMER_DEFAULT;
//    velocity.y = -250;
//    velocity.x = (rand() % 100) - 50;
//    updateCollision();
//}

//void Spiny::HandleTileCollision(const Tile& tile, CollisionType ct) {
//    if (isDying()) return;
//
//    if (ct == COLLISION_TYPE_EAST || ct == COLLISION_TYPE_WEST) {
//        // Đổi chiều đi khi chạm tường
//        direction = (direction == LEFT ? RIGHT : LEFT);
//        if (ct == COLLISION_TYPE_EAST)
//            setX(tile.getX() - getWidth());
//        else
//            setX(tile.getX() + tile.getWidth());
//        velocity.x = -velocity.x;
//        UpdateTexture();
//    }
//    else if (ct == COLLISION_TYPE_SOUTH) {
//        // Đứng trên đất
//        setY(tile.getY() - getHeight());
//        velocity.y = 0;
//        state = ON_GROUND;
//    }
//    else if (ct == COLLISION_TYPE_NORTH) {
//        // Bị chặn từ dưới
//        setY(tile.getY() + tile.getHeight());
//        velocity.y = 0;
//    }
//}