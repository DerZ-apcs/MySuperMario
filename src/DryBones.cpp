#include "DryBones.h"
#include "ResourceManager.h"

DryBones::DryBones(Vector2 pos, Texture2D tex)
	: Enemy(pos, { 32,48 }, { 0,0 }, LEFT, ON_GROUND, tex, 0.2f, 1, WHITE),
	dbState(DB_ALIVE),
	breakTimer(0), reviveTimer(0), shakeTimer(0)
{
}

void DryBones::Update() {
    float dt = GetFrameTime();

    switch (dbState) {
    case DB_ALIVE:
        velocity.x = (direction == LEFT ? -WALK_SPEED : WALK_SPEED);
        Enemy::Update();
        break;

    case DB_BROKEN:
        breakTimer -= dt;
        if (breakTimer <= 0) {
            dbState = DB_REVIVING;
            reviveTimer = REVIVE_DURATION;
            shakeTimer = REVIVE_DURATION;
            Singleton<ResourceManager>::getInstance().playSound("DRYBONES_REVIVE");
        }
        break;

    case DB_REVIVING:
        reviveTimer -= dt;
        if (reviveTimer <= 0) {
            // trở về alive
            dbState = DB_ALIVE;
            // reset hướng ngẫu nhiên
            direction = (rand() % 2 == 0 ? LEFT : RIGHT);
            // khôi phục collider
            updateCollision();
        }
        break;
    }
}

void DryBones::draw() {
    Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle destRec = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
    switch (dbState) {
    case DB_ALIVE:
        Enemy::draw();
        break;

    case DB_BROKEN:
        DrawTexturePro(
            Singleton<ResourceManager>::getInstance().getTexture("DryBones_Collapse"),
            sourceRec, destRec, { 0,0 }, 0, WHITE);
        break;

    case DB_REVIVING:
        // hiệu ứng rung: alternate alpha
        shakeTimer -= GetFrameTime();
        {
            float alpha = (int(shakeTimer * 10) % 2 == 0 ? 0.5f : 1.0f);
            DrawTexturePro(
                Singleton<ResourceManager>::getInstance().getTexture(
                    std::string("DryBones_") + (direction == LEFT ? "LEFT" : "RIGHT") + "_0"
                ), sourceRec, destRec, { 0,0 }, 0, Fade(WHITE, alpha));
        }
        break;
    }
#ifdef DEBUG
    CollNorth.draw(); CollSouth.draw(); CollEast.draw(); CollWest.draw();
#endif
}

void DryBones::CollisionWithCharacter(Mario& m, CollisionType ct) {
    if (dbState != DB_ALIVE) return;

    // stomp từ trên xuống
    if (ct == COLLISION_TYPE_SOUTH && (m.getState()==JUMPING || m.getState()==FALLING)) {
        dbState = DB_BROKEN;
        breakTimer = BREAK_DURATION;
        velocity = { 0,0 };
        m.setVelY(-MARIO_BOUNCE_VELOCITY);
        m.addScore(SCORE_STOMP_GOOMBA);
        Singleton<ResourceManager>::getInstance().playSound("STOMP");
        return;
    }

    // va chạm thường gây sát thương
    if ((ct == COLLISION_TYPE_EAST || ct == COLLISION_TYPE_WEST || ct == COLLISION_TYPE_NORTH)
        && m.getInvincibilityTimer() <= 0) {
        if (m.getMarioState() == STATE_SUPER || m.getMarioState() == STATE_FIRE_BALL) {
            m.TransitionToSmall();
            m.setInvincibilityTimer(2.0f);
        }
        else {
            m.setState(STATE_IS_DYING);
            Singleton<ResourceManager>::getInstance().playSound("MARIO_DIE");
        }
    }
}

void DryBones::HandleTileCollision(const Tile& t, CollisionType ct) {
    if (dbState != DB_ALIVE) return;
    // đổi hướng khi chạm tường
    if (ct == COLLISION_TYPE_EAST || ct == COLLISION_TYPE_WEST) {
        direction = (direction == LEFT ? RIGHT : LEFT);
        velocity.x = (direction == LEFT ? -WALK_SPEED : WALK_SPEED);
        return;
    }
    // xử lý chạm đất/đỉnh như bình thường
    Enemy::HandleTileCollision(t, ct);
}


