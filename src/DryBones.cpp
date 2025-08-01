#include "../include/DryBones.h"
#include "../include/GameEngine.h"

DryBones::DryBones(Vector2 pos, Texture2D tex)
    : Enemy(pos, { 32, 43 }, { 0,0 }, LEFT, ON_GROUND, tex, 0.2f, 1, WHITE),
    dbState(DB_ALIVE),
    breakTimer(0), reviveTimer(0), shakeTimer(0)
{
}

void DryBones::Update() {
    float dt = GetFrameTime();
    Entity::Update();
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
            RESOURCE_MANAGER.playSound("DRYBONES_REVIVE");
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
    updateCollision();
	UpdateTexture();
}

void DryBones::UpdateTexture() {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("DryBones_Dead");
        return;
    }
    const float deltaTime = getFrameTime();
	std::string dir = (direction == LEFT ? "LEFT" : "RIGHT");
    if (dbState == DB_ALIVE) {
        // Chọn texture dựa trên hướng và trạng thái
		frameAcum += deltaTime;
		if (frameAcum > frameTime) {
			currFrame = (currFrame + 1) % (maxFrame + 1);
			frameAcum = 0;
		}
        texture = RESOURCE_MANAGER.getTexture("DryBones_" + dir + std::to_string(currFrame));
    }
    else if (dbState == DB_BROKEN) {
        texture = RESOURCE_MANAGER.getTexture("DryBones_Collapse");
    }
    else if (dbState == DB_REVIVING) {
        // Chọn texture dựa trên hướng và trạng thái
        texture = RESOURCE_MANAGER.getTexture("DryBones_" + dir + "_0");
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
            RESOURCE_MANAGER.getTexture("DryBones_Collapse"),
            sourceRec, destRec, { 0,0 }, 0, WHITE);
        break;

    case DB_REVIVING:
        // hiệu ứng rung: alternate alpha
        shakeTimer -= GetFrameTime();
        {
            float alpha = (int(shakeTimer * 10) % 2 == 0 ? 0.5f : 1.0f);
            DrawTexturePro(
                RESOURCE_MANAGER.getTexture(
                    std::string("DryBones_") + (direction == LEFT ? "LEFT" : "RIGHT") + "_0"
                ), sourceRec, destRec, { 0,0 }, 0, Fade(WHITE, alpha));
        }
        break;
    }
    if (SETTING.getDebugMode()) {
        CollNorth.draw(); 
        CollSouth.draw();
        CollEast.draw(); 
        CollWest.draw();
    }
}

ENEMY_TYPE DryBones::getEnemyType() const
{
    return DRYBONES;
}

float DryBones::getScores() const
{
    return SCORE_STOMPED_DRYBONES;
}

void DryBones::stomped()
{
	if (dbState != DB_ALIVE) return;
	dbState = DB_BROKEN;
	breakTimer = BREAK_DURATION;
	velocity = { 0,0 };
	// hiệu ứng squash
	updateSquashEffect();
	Effect* text = new TextEffect(std::to_string(SCORE_STOMPED_DRYBONES).c_str(), getCenter());
	globalGameEngine->addEffect(text);
}

