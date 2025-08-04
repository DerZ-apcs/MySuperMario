#include "../include/DryBones.h"
#include "../include/GameEngine.h"

DryBones::DryBones(Vector2 pos, Texture2D tex)
    : Enemy(pos, { 32, 43 }, { 0,0 }, LEFT, ON_GROUND, tex, 1.5f, 1, WHITE),
    dbState(DB_ALIVE),
    breakTimer(0), reviveTimer(0), shakeTimer(0)
{
	texture = RESOURCE_MANAGER.getTexture("DryBones_LEFT_0");
	frameTime = 1.5f;
    maxFrame = 1;
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
    if (velocity.y > 20) state = FALLING;
	velocity.y += GRAVITY * dt; // Gravity effect
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
    updateCollision();
	UpdateTexture();
}

void DryBones::UpdateTexture() {
    if (isDead() || state == STATE_IS_DYING) {
        texture = RESOURCE_MANAGER.getTexture("DryBones_Dead");
        return;
    }
    const float deltaTime = getFrameTime();
	std::string dir = (direction == LEFT ? "_LEFT_" : "_RIGHT_");
    if (dbState == DB_ALIVE) {
        // Chọn texture dựa trên hướng và trạng thái
        frameAcum += deltaTime;
        if (frameAcum > frameTime) {
            currFrame++;
			if (currFrame > maxFrame) {
				currFrame = 0;
			}
            frameAcum = 0;
        }
        if (state == ON_GROUND)
            texture = RESOURCE_MANAGER.getTexture("DryBones" + dir + std::to_string(currFrame));
        else if (state == FALLING || state == JUMPING) {
            texture = RESOURCE_MANAGER.getTexture("DryBones" + dir + "0");
        }
    }
    else if (dbState == DB_BROKEN) {
        texture = RESOURCE_MANAGER.getTexture("DryBones_Collapse");
    }
    else if (dbState == DB_REVIVING) {
        // Chọn texture dựa trên hướng và trạng thái
        texture = RESOURCE_MANAGER.getTexture("DryBones" + dir + "0");
    }
}
void DryBones::draw() {
    Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle destRec = { position.x, position.y, texture.width * squashScale, texture.height * squashScale };
    if (dbState == DB_ALIVE || dbState == DB_BROKEN) {
        Enemy::draw();
    }
    else {
        shakeTimer -= GetFrameTime();
        {
            float alpha = (int(shakeTimer * 10) % 2 == 0 ? 0.5f : 1.0f);
            DrawTexturePro(texture, sourceRec, destRec, { 0,0 }, 0, Fade(WHITE, alpha));
        }
        if (SETTING.getDebugMode()) {
            CollNorth.draw();
            CollSouth.draw();
            CollEast.draw();
            CollWest.draw();
        }
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
	Effect* score = new ScoreEffect(RESOURCE_MANAGER.getTexture(std::to_string(SCORE_STOMPED_DRYBONES).c_str()), getCenter());
	globalGameEngine->addEffect(score);
}

