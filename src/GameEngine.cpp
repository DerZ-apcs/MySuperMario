#include "../include/GameEngine.h"
#include <iostream>

GameEngine* globalGameEngine = nullptr;

GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, Mario*& player)
    : /*camera(screenWidth, screenHeight, 1.75f),*/ level(&level), player(player) {
    map.LoadFromJsonFile(level.getMapPath());
    map.loadBackgroundTexture(level.getBackGroundName());
    Vector2 Msize = map.getMapSize();
    //camera.loadRenderTexture(Msize);
    // camera
    //player = new Mario();

    camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = player->getPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    /*blocks = map.getBlocks();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();*/
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
    BackGroundPos = { {0, 0}, {(float)GetScreenWidth(), 0}, {(float)GetScreenWidth() * 2, 0} };
}

GameEngine::~GameEngine() {
    for (size_t i = 0; i < fireball.size(); i++)
        delete fireball[i];
    player = nullptr;
    fireball.clear();
}

//void GameEngine::addScore(int amount) {
//    player->setScores(player->getScores() + amount);
//}

void GameEngine::addFireBall(FireBall* fireball) {
    this->fireball.push_back(fireball);
}

// update
void GameEngine::update()
{
    if (IsKeyPressed(KEY_ENTER) || GUI::setting_is_pressed) {
        if (GUI::setting_is_pressed) 
            GUI::setting_is_pressed = false;
        isPaused = !isPaused;
        if (died)
        {
            died = false;
            player->setLostLife(false);
            player->resetInGame();
            resetGame();
            resetTimer();
        }
        else if (isPaused) {
            RESOURCE_MANAGER.playSound("pause.wav");
        }
    }
    if (GUI::restart_is_pressed) {
        GUI::restart_is_pressed = false;
        player->reset();
        resetGame();
        resetTimer();
    }
    if (isPaused || cleared) {
        return;
    }
    if (player != nullptr) {
        camera.target.y = GetScreenHeight() / 2.0f;
        if (player->getX() >= GetScreenWidth() / 2.0f) {
            camera.target.x = player->getX();
        }
        else camera.target.x = GetScreenWidth() / 2.0f;

        for (int i = 0; i < 3; i++) {
            // wrap from left to far most right
            if (BackGroundPos[i].x + map.BgWidth <= player->getX() - map.BgWidth / 2.0f) {
                float maxX = BackGroundPos[0].x;
                for (int j = 1; j < 3; j++) {
                    if (BackGroundPos[j].x > maxX) maxX = BackGroundPos[j].x;
                }
                BackGroundPos[i].x = maxX + map.BgWidth;
            }
            // wrap from right to left
            if (BackGroundPos[i].x + map.BgWidth / 2.0f >= player->getX() + map.BgWidth * 2) {
                float minX = BackGroundPos[i].x;
                for (int j = 1; j < 3; j++) {
                    if (BackGroundPos[j].x < minX) minX = BackGroundPos[j].x;
                }
                BackGroundPos[i].x = minX - map.BgWidth;
            }
        }
        // tiles (collision with character)
        for (auto const& tile : *map.getVectorTiles()) {
            CollisionType PlayerCollision = player->CheckCollision(*tile);
            if (PlayerCollision != COLLISION_TYPE_NONE && player->getCollisionAvailable() == true)
                mediatorCollision.HandleCollision(player, tile);

            for (auto& fireball : *player->getFireBalls()) {
                CollisionType FireBallCollision = fireball->CheckCollision(*tile);
                if (FireBallCollision != COLLISION_TYPE_NONE)
                    mediatorCollision.HandleCollision(fireball, tile);
            }
        }
        player->Update();
        //camera.update(player->getX(), player->getY());
    }
    else
        cout << "Null player " << endl;
}

void GameEngine::handleCollision()
{

}
// draw
void GameEngine::draw()
{
    BeginDrawing();
    BeginMode2D(camera);
    //camera.beginDrawing();
    map.drawBackGround();
    map.drawMap();

    //ClearBackground(SKYBLUE);
    /*camera.render();
    camera.endDrawing();*/
    if (player) 
        player->draw();
    EndMode2D();

    if (player) {
        bool lostLife = player->isLostLife();

        if (!lostLife) {
            GUI::drawStatusBar(player);
        }
        if (isPaused) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
            if (cleared) {
                GUI::drawLevelClear();
            }
            else if (gameover) {
                GUI::drawGameOverScreen();
            }
            else if (died)
                GUI::drawDeathScreen();
            else {
                GUI::drawPauseMenu();
                if (GUI::sound_is_pressed) {
                    GUI::sound_is_pressed = false;
                    if (SETTING.isMusicEnabled()) {
                        SETTING.setMusic(false);
                    }
                    else SETTING.setMusic(true);
                }
            }
        }
    }
    EndDrawing();
}

// run
bool GameEngine::run() {
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    // load and play the new music

    // second game loop (main game loop)
    while (!WindowShouldClose()) {
        if (SETTING.isMusicEnabled()) {
            UpdateMusicStream(RESOURCE_MANAGER.getMusic(level->getMusic()));
        }

        update();
        ClearBackground(RAYWHITE);
        draw();
        
        if (cleared == true && isPaused == false) {
            RESOURCE_MANAGER.stopCurrentMusic();
            RESOURCE_MANAGER.playMusic("MUSIC_1");
            return true;
        }

        if (gameover && !isPaused) break;
        if (GUI::home_is_pressed) {
            GUI::home_is_pressed = false;
            break;
        }

        // out of time
        if (this->time <= 0) player->setLostLife(true);
        // set lost life for falling out of bound
        if (player->getY() > getBound().y && player->getPhase() != Phase::CLEARLEVEL_PHASE)
            player->setLostLife(true);

        // clear level
        if (!player->getExitLevel() && player->getX() >= map.getMapSize().x - 100.f && player->getState() == ON_GROUND) { // clear level (when character enter near the end of level)
            player->setVictory(true);
            player->setVel({ 0, 0 });
            RESOURCE_MANAGER.stopCurrentMusic();
            RESOURCE_MANAGER.playSound("level_clear.wav");
        }
        if ((player->getExitLevel()) && (player->getPhase() != Phase::CLEARLEVEL_PHASE)) {
            player->setPhase(Phase::CLEARLEVEL_PHASE);
        }
        if (player->getX() >= map.getMapSize().x - 10 && player->getPhase() == CLEARLEVEL_PHASE) {
            cleared = true;
            isPaused = true;
            player->setVel({ 0, 0 });
        }
        else if (player->isLostLife() && player->getTop() > getBound().y) { // when finish the animation of dying (flying to the top)
            if (player->getLives() < 0) {
                gameover = true;
                isPaused = true;
            }
            else {
                died = true;
                isPaused = true;
            }
        }
        else if (player->isLostLife()) { // set animation & sound when dying
            if (player->getPhase() != DEAD_PHASE) {
                RESOURCE_MANAGER.stopCurrentMusic();
                player->setPhase(DEAD_PHASE);
                if (player->getLives() < 0) {
                    RESOURCE_MANAGER.playSound("game_over.wav");
                }
                else {
                    RESOURCE_MANAGER.playSound("lost_life.wav");
                }
            }
        }

    } 
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic("TITLE");
    return false;
}

string GameEngine::getCurrentMapName()
{
    return level->getName();
}

float GameEngine::getGlobalTime() const 
{
    return deltaTime;
}

float GameEngine::getRemainingTime() const
{
    return this->time;
}

float GameEngine::resetTimer()
{
    this->time = 300;
    return 300.f;
}

bool GameEngine::isOver() const
{
    return gameover;
}

void GameEngine::resetGame()
{
    map.clear();

    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    map.LoadFromJsonFile(level->getMapPath());
    map.loadBackgroundTexture(level->getBackGroundName());
    isPaused = false;
    this->time = 300;
    resetTimer();
}

Vector2 GameEngine::getBound()
{
    return map.getMapSize();
}

