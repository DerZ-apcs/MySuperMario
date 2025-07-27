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
    mediatorCollision.SetMario(&mario);
    // enemies.push_back(new Goomba({ 400, 920 }, Resource_manager.getTexture("Goomba_LEFT_0"), &mediatorCollision));
   
    // enemies.push_back(new FlyingGoomba({ 400, 900 }, Resource_manager.getTexture("Goomba_LEFT_0"), &mediatorCollision));
    
    // enemies.push_back(new BlueKoopa({ 400, 912 }, Resource_manager.getTexture("BlueKoopa_RIGHT_1")));
	// enemies.push_back(new GreenKoopa({ 400, 912 }, Resource_manager.getTexture("GreenKoopa_RIGHT_1")));
	// enemies.push_back(new YellowKoopa({ 400, 912 }, Resource_manager.getTexture("YellowKoopa_RIGHT_1")));
    // enemies.push_back(new ParaKoopaRed({ 400, 912 }, Resource_manager.getTexture("ParaKoopaRed_RIGHT_1")));
    // enemies.push_back(new PiranhaPlant({ 576, 448 }, Resource_manager.getTexture("PiranhaPlant_OPEN"),mario));
    // enemies.push_back(new FirePiranhaPlant({ 576, 448 }, Resource_manager.getTexture("FirePiranhaPlant_OPEN"), mario));
	// enemies.push_back(new RapidFirePiranha({ 577, 448 }, Resource_manager.getTexture("FirePiranhaPlant_OPEN"), mario));
    // enemies.push_back(new HomingFirePiranha({ 576, 448 }, Resource_manager.getTexture("FirePiranhaPlant_OPEN"), mario));
     
	// enemies.push_back(new Bullet({ 2000, 350 }, Resource_manager.getTexture("Bullet_LEFT_1"), LEFT));
    // enemies.push_back(new FireBullet({ 2000, 350 }, Resource_manager.getTexture("Bullet_LEFT_1"), LEFT, mario));
     
    // enemies.push_back(new Rex({ 400, 912 }, Resource_manager.getTexture("Rex_LEFT_0")));
    
    // enemies.push_back(new Muncher({ 450,448 }, Resource_manager.getTexture("Muncher_1"))); 

	// enemies.push_back(new BobOmb({ 400, 912 }, Resource_manager.getTexture("BobOmb_RIGHT_0"), &mediatorCollision));

	enemies.push_back(new JumpingPiranhaPlant({ 576, 440 }, Resource_manager.getTexture("PiranhaPlant_JUMPING"), mario));
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
    static const int MAX_TOTAL_FIREBALLS = 50;
    int totalFireballs = 0;
    for (auto& enemy : enemies) {
        Bullet* bullet = dynamic_cast<Bullet*>(enemy);
        if (bullet) {
            totalFireballs += bullet->getFireBalls()->size();
        }
    }
    if (totalFireballs > MAX_TOTAL_FIREBALLS) {
        for (auto& enemy : enemies) {
            Bullet* bullet = dynamic_cast<Bullet*>(enemy);
            if (bullet && !bullet->getFireBalls()->empty()) {
                auto* fireball = bullet->getFireBalls()->front();
                bullet->getFireBalls()->pop_front();
                delete fireball;
                break;
            }
        }
    }

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

    mario.Update();

    for (auto& enemy : enemies) {
        if (!enemy) continue;

        enemy->Update();

        for (auto const& tile : *map1.getVectorTiles()) {
            CollisionType enemyCollision = enemy->CheckCollision(*tile);
            if (enemyCollision != COLLISION_TYPE_NONE) {
                enemy->HandleTileCollision(*tile, enemyCollision);
            }
        }

        mediatorCollision.HandleCollision(&mario, enemy);

        for (auto& other : enemies) {
            if (enemy != other) {
                CollisionType enemyCollision = enemy->CheckCollision(*other);
                if (enemyCollision != COLLISION_TYPE_NONE) {
                    enemy->CollisionWithEnemy(*other, enemyCollision);
                }
            }
        }

        for (auto& fireball : *mario.getFireBalls()) {
            if (!fireball->IsDestroyed()) {
                mediatorCollision.HandleCollision(fireball, enemy);
            }
        }

        Bullet* bullet = dynamic_cast<Bullet*>(enemy);
        if (bullet) {
            for (auto& fireball : *bullet->getFireBalls()) {
                if (!fireball->IsDestroyed()) {
                    mediatorCollision.HandleCollision(fireball, &mario);
                    for (auto const& tile : *map1.getVectorTiles()) {
                        CollisionType tileColl = fireball->CheckCollision(*tile);
                        if (tileColl != COLLISION_TYPE_NONE) {
                            mediatorCollision.HandleCollision(fireball, tile);
                        }
                    }
                }
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* enemy) {
        if (enemy && enemy->isReadyForRemoval()) {
            delete enemy;
            return true;
        }
        return false;
        }), enemies.end());

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

    auto& fireballs = *mario.getFireBalls();
    fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](FireBall* fireball) {
        if (fireball && (fireball->isMaxDistance() || fireball->IsDestroyed())) {
            delete fireball;
            return true;
        }
        return false;
        }), fireballs.end());
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