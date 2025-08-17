// ParaKoopa.cpp
#include "../include/ParaKoopa.h"
#include "../include/ResourceManager.h"

static constexpr float RED_JUMP_INTERVAL = 2.5f;
static constexpr float RED_JUMP_VELOCITY = 250.0f;
static constexpr float RED_RUN_SPEED = 80.0f;

static constexpr float BLUE_JUMP_INTERVAL = 1.2f;
static constexpr float BLUE_JUMP_VELOCITY = 180.0f;
static constexpr float BLUE_RUN_SPEED = 40.0f;

ParaKoopa::ParaKoopa(Vector2 pos, Texture2D texture)
    : Koopa(pos, texture), jumpTimer(0.0f),
    paraKoopaType(RED_PARAKOOPA)
{
    scores = SCORE_STOMP_KOOPA;
}

float ParaKoopa::getScores() const
{
    return scores;
}

ENEMY_TYPE ParaKoopa::getEnemyType() const
{
    return PARAKOOPA;
}

void ParaKoopa::loadEntity(const json& j)
{
    Koopa::loadEntity(j);
    jumpTimer = j["jumpTimer"];
    paraKoopaType = static_cast<PARAKOOPA_TYPE>(j["paraKoopaType"].get<int>());
}

void ParaKoopa::saveEntity(json& j) const
{
    Koopa::saveEntity(j);
    j["jumpTimer"] = jumpTimer;
    j["paraKoopaType"] = static_cast<int>(paraKoopaType);
}

ParaKoopaRed::ParaKoopaRed(Vector2 pos, Texture2D texture) : ParaKoopa(pos, texture) {
    paraKoopaType = RED_PARAKOOPA;
}

void ParaKoopaRed::Update() {
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > RED_JUMP_INTERVAL) {
        velocity.y = -RED_JUMP_VELOCITY;
		  state = JUMPING;
        jumpTimer = 0.0f;
    }
    Koopa::Update();
}

void ParaKoopaRed::UpdateTexture() {
    if (koopaState == SHELL_KOOPA || state == STATE_IS_DYING) {
        if (koopaState == SHELL_KOOPA && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture("ParaKoopaRed_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = RESOURCE_MANAGER.getTexture("ParaKoopaRed_Shell_3");
        }
        return;
    }

    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }
    if (direction == LEFT) {
        texture = RESOURCE_MANAGER.getTexture("ParaKoopaRed_LEFT_" + std::to_string(currFrame));
    }
    else {
        texture = RESOURCE_MANAGER.getTexture("ParaKoopaRed_RIGHT_" + std::to_string(currFrame));
    }
}

void ParaKoopaRed::saveEntity(json& j) const {
    ParaKoopa::saveEntity(j);

    // Add Tiled-compatible properties array
    j["properties"] = json::array({
        {
            { "name", "Name" },
            { "type", "string" },
            { "value", "Enemy" }
        },
        {
            { "name", "Type" },
            { "type", "string" },
            { "value", "ParaKoopaRed"}
        }
        });
}

ParaKoopaBlue::ParaKoopaBlue(Vector2 pos, Texture2D texture)
    : ParaKoopa(pos, texture) {
    paraKoopaType = BLUE_PARAKOOPA;
}

void ParaKoopaBlue::Update() {
    jumpTimer += GetFrameTime();
    if (state == ON_GROUND && jumpTimer > BLUE_JUMP_INTERVAL) {
        velocity.y = -BLUE_JUMP_VELOCITY;
 	      state = JUMPING;
        jumpTimer = 0.0f;
    }

    Koopa::Update();
}

void ParaKoopaBlue::UpdateTexture() {
    if (koopaState == SHELL_KOOPA || state == STATE_IS_DYING) {
        if (koopaState == SHELL_KOOPA && velocity.x != 0) {
            frameAcum += GetFrameTime();
            if (frameAcum > 0.05f) {
                currFrame = (currFrame + 1) % 4;
                frameAcum = 0;
            }
            texture = RESOURCE_MANAGER.getTexture("BlueKoopa_Shell_" + std::to_string(currFrame));
        }
        else {
            texture = RESOURCE_MANAGER.getTexture("BlueKoopa_Shell_3");
        }
        return;
    }
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0;
    }
    if (direction == LEFT) {
        texture = RESOURCE_MANAGER.getTexture("ParaKoopaBlue_LEFT_" + std::to_string(currFrame));
    }
    else {
        texture = RESOURCE_MANAGER.getTexture("ParaKoopaBlue_RIGHT_" + std::to_string(currFrame));
    }
}

ParaKoopaGreen::ParaKoopaGreen(Vector2 pos, Texture2D texture):
    ParaKoopa(pos, texture)
{
    paraKoopaType = GREEN_PARAKOOPA;
}

void ParaKoopaGreen::Update()
{
}

void ParaKoopaGreen::UpdateTexture()
{
}

ParaKoopaYellow::ParaKoopaYellow(Vector2 pos, Texture2D texture):
    ParaKoopa(pos, texture)
{
    paraKoopaType = YELLOW_PARAKOOPA;
}

void ParaKoopaYellow::Update()
{
}

void ParaKoopaYellow::UpdateTexture()
{
}
