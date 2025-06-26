#include "../include/Game.h"
#include "../include/Map.h"
#include <iostream>

Game::Game() : Game(1200, 800, 140)
{
}

Game::Game(int nwidth, int nheight, int ntargetFPS) :
    width(nwidth), height(nheight), targetFPS(ntargetFPS), Resource_manager(Singleton<ResourceManager>::getInstance()) {
    Resource_manager.LoadAllResources();
    map1.LoadFromJsonFile(Map::basePath + "MAP_1.1.json");
    BgWidth = (float)GetScreenWidth();
    BgHeight = (float)GetScreenHeight();
    BackGroundTex = Singleton<ResourceManager>::getInstance().getTexture("BACKGROUND_1");
    BackGroundPos = { {0, 0}, {BgWidth, 0}, {BgWidth * 2, 0} };
    camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = mario.getPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    enemies.push_back(new Goomba({ 400, 920 }, Resource_manager.getTexture("Goomba_LEFT_0")));
    enemies.push_back(new Goomba({ 300, 920 }, Resource_manager.getTexture("Goomba_LEFT_1")));
    enemies.push_back(new Koopa({ 500, 912 }, Resource_manager.getTexture("Koopa_LEFT_1")));
    enemies.push_back(new FlyingGoomba({ 600, 920 }, Resource_manager.getTexture("FlyingGoomba_LEFT_0")));
}

Game::~Game()
{
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    Singleton<ResourceManager>::getInstance().UnloadAllResources();
}

void Game::initGame()
{
    SetTargetFPS(targetFPS);
    Resource_manager.playMusic("MUSIC1");

    while (!WindowShouldClose()) {
        UpdateGame();
        UpdateMusicStream(Resource_manager.getMusic("MUSIC1"));
        ClearBackground(RAYWHITE);
        BeginDrawing();
        draw();
        EndDrawing();
    }
}

void Game::UpdateGame() {
    // Camera & background
    camera.target.y = GetScreenHeight() / 2.0f;
    if (mario.getX() >= GetScreenWidth() / 2.0f) {
        camera.target.x = mario.getX();
    }
    else {
        camera.target.x = GetScreenWidth() / 2.0f;
    }

    for (int i = 0; i < 3; i++) {
        if (BackGroundPos[i].x + BgWidth <= mario.getX() - BgWidth / 2.0f) {
            float maxX = BackGroundPos[0].x;
            for (int j = 1; j < 3; j++) {
                if (BackGroundPos[j].x > maxX) maxX = BackGroundPos[j].x;
            }
            BackGroundPos[i].x = maxX + BgWidth;
        }
        if (BackGroundPos[i].x + BgWidth / 2.0f >= mario.getX() + BgWidth * 2) {
            float minX = BackGroundPos[0].x;
            for (int j = 1; j < 3; j++) {
                if (BackGroundPos[j].x < minX) minX = BackGroundPos[j].x;
            }
            BackGroundPos[i].x = minX - BgWidth;
        }
    }

    // Update Mario
    mario.Update();

    // Update enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemy* enemy = *it;
        if (!enemy) {
            it = enemies.erase(it);
            continue;
        }
        enemy->Update();
        // Check collision with tiles
        for (auto const& tile : *map1.getVectorTiles()) {
            CollisionType enemyCollision = enemy->CheckCollision(*tile);
            if (enemyCollision != COLLISION_TYPE_NONE) {
                enemy->HandleTileCollision(*tile, enemyCollision);
            }
        }
        // Check collision with Mario
        mediatorCollision.HandleCollision(&mario, enemy);
        // Check collision with other enemies
        for (auto other = enemies.begin(); other != enemies.end(); ++other) {
            if (enemy != *other) {
                CollisionType enemyCollision = enemy->CheckCollision(**other);
                if (enemyCollision != COLLISION_TYPE_NONE) {
                    enemy->CollisionWithEnemy(**other, enemyCollision);
                }
            }
        }
        // Remove dead enemies
        if (enemy->isDying()) {
            delete enemy;
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }

    // Tiles and Mario/Fireball collisions
    for (auto const& tile : *map1.getVectorTiles()) {
        CollisionType PlayerCollision = mario.CheckCollision(*tile);
        if (PlayerCollision != COLLISION_TYPE_NONE)
            mediatorCollision.HandleCollision(&mario, tile);
        for (auto& fireball : *mario.getFireBalls()) {
            CollisionType FireBallCollision = fireball->CheckCollision(*tile);
            if (FireBallCollision != COLLISION_TYPE_NONE)
                mediatorCollision.HandleCollision(fireball, tile);
        }
    }
}

void Game::draw()
{
    BeginMode2D(camera);
    drawBackGround();
    mario.draw();
    map1.drawMap();
    for (auto& enemy : enemies) {
        enemy->draw();
    }
    EndMode2D();
}

void Game::drawBackGround() const
{
    ClearBackground(SKYBLUE);
    for (int i = 0; i < 3; i++) {
        DrawTexturePro(BackGroundTex, { 0, 0, (float)BackGroundTex.width, (float)BackGroundTex.height },
            { BackGroundPos[i].x, BackGroundPos[i].y, BgWidth, BgHeight },
            { 0, 0 }, 0.0f, WHITE);
    }
}

int Game::getWidth() const {
    return width;
}
int Game::getHeight() const {
    return height;
}
int Game::getTergetFPS() const {
    return targetFPS;
}
void Game::setWidth(int width) {
    this->width = width;
}
void Game::setHeight(int height) {
    this->height = height;
}
void Game::setTargetFPS(int targetFPS) {
    this->targetFPS = targetFPS;
}