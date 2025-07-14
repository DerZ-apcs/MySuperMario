#include "../include/GameEngine.h"
#include"../include/Character.h"
#include "../include/GUI.h"
#include "../include/Effect.h"
#include "../include/Enemy.h"
#include "../include/Coin.h"
#include "../include/Map.h"
#include "../include/Level.h"
#include "../include/Goomba.h"
#include "../include/Koopa.h"
#include "../include/Rex.h"
#include "../include/Bullet.h"
#include <iostream>

GameEngine* globalGameEngine = nullptr;

GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player)
    : camera(screenWidth, screenHeight, 1.25f), level(&level), player(player) {
    map.LoadFromJsonFile(level.getMapPath());
    map.loadBackgroundTexture(level.getBackGroundName());
    Vector2 Msize = map.getMapSize();
    camera.loadRenderTexture(Msize);
    // camera
    if (!player) player = new Mario();


    blocks = map.getBlocks();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
    BackGroundPos = { {0, 0}, {(float)GetScreenWidth(), 0}, {(float)GetScreenWidth() * 2, 0} };
    //items.push_back();
    for (int i = 0; i < 10; i++) {
        Coin* coin = new Coin(STATIC_COIN, { (float)i * 50, 600 });
        items.push_back(coin);
    }
    /*for (int i = 7; i < 10; i++) {
        Goomba* goomba = new Goomba({(float) 100 * i, 300 }, RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0"));
        goomba->setState(FALLING);
        enemies.push_back(goomba);
    }*/
    /*for (int i = 9; i <= 10; i++) {
        FlyingGoomba* flyingGoomba = new FlyingGoomba({ (float)50 * i, 300 }, RESOURCE_MANAGER.getTexture("FlyingGoomba_LEFT_0"));
        flyingGoomba->setState(FALLING);
        enemies.push_back(flyingGoomba);
    }*/
    Koopa* koopa = new Koopa({ 300, 500 }, RESOURCE_MANAGER.getTexture("Koopa_LEFT_0"));
    koopa->setState(FALLING);
    enemies.push_back(koopa);

    Rex* rex = new Rex({ 400, 500 }, RESOURCE_MANAGER.getTexture("Rex_LEFT_0"));
    rex->setState(FALLING);
    enemies.push_back(rex);

    Bullet* bullet1 = new Bullet({ 1000, 400 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
    enemies.push_back(bullet1);
    FireBullet* bullet2 = new FireBullet({ 1600, 500 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
    enemies.push_back(bullet2);
    Bullet* bullet3 = new Bullet({ 1000, 600 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
    enemies.push_back(bullet3);

    
}

GameEngine::~GameEngine() {
    for (size_t i = 0; i < enemyFireball.size(); i++)
        delete enemyFireball[i];
    for (size_t i = 0; i < enemies.size(); i++)
        delete enemies[i];
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
    player = nullptr;
    enemyFireball.clear();
    blocks.clear();
    enemies.clear();
    items.clear();
    effects.clear();
    decor.clear();
}

void GameEngine::addScore(int amount) {
    player->setScores(player->getScores() + amount);
}

void GameEngine::addEnemyFireBall(EnemyFireBall* fireball) {
    this->enemyFireball.push_back(fireball);
}

void GameEngine::addEnemy(Enemy* enemy)
{
    this->enemies.push_back(enemy);
}

void GameEngine::addEffect(Effect* effect)
{
    this->effects.push_back(effect);
}

void GameEngine::addItem(Item* item)
{
    this->items.push_back(item);
}

// update
void GameEngine::update()
{
    if (!player) {
        cout << "NULL player" << endl;
        return;
    }

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
    // let the pause and clear screen idling
    if (isPaused || cleared) {
        return;
    }
    // set Time 
    const float deltaTime = GetFrameTime();
    this->time -= deltaTime;

    // update background

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
    for (size_t i = 0; i < enemyFireball.size(); i++) {
        if (enemyFireball[i]->isDead() || enemyFireball[i]->isMaxTime()) {
            delete enemyFireball[i];
            enemyFireball.erase(enemyFireball.begin() + i);
            i--;
        }
        else
            enemyFireball[i]->Update();
    }

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i]->isDead()) {
            delete blocks[i];
            blocks.erase(blocks.begin() + i);
            i--;
        }
        else
            blocks[i]->Update();
    }

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->isDead()) {
            delete items[i];
            items.erase(items.begin() + i);
            i--;
        }
        else
            items[i]->Update();
    }

    for (size_t i = 0; i < effects.size(); i++) {
        if (effects[i]->isDead()) {
            delete effects[i];
            effects.erase(effects.begin() + i);
            i--;
        }
        else
            effects[i]->Update();
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->isDead()) {
            delete enemies[i];
            enemies[i] = nullptr;
            enemies.erase(enemies.begin() + i);
            i--;
        }
        else
            enemies[i]->Update();
    }

    // player udpate
    player->Update();
    // all collision
    handleCollision();
    // camera update
    camera.update(player->getX(), player->getY());
}

void GameEngine::handleCollision()
{    
    // tiles (collision with character)
    CollisionInterface CollI;
    bool isGrounded = false;
    for (size_t j = 0; j < blocks.size(); j++) {
        if (CollI.HandleCollision(player, blocks[j]))
            isGrounded = true;
        //PlayerBlockInfo Infor;
        //Infor.HandleCollision(player, blocks[j]);
        for (size_t i = 0; i < enemies.size(); i++)
            CollI.HandleCollision(enemies[i], blocks[j]);

        for (size_t i = 0; i < items.size(); i++) 
            CollI.HandleCollision(items[i], blocks[j]);

        for (auto& fireball : *player->getFireBalls()) {
            CollI.HandleCollision(fireball, blocks[j]);
        }
        for (size_t i = 0; i < enemyFireball.size(); i++)
            CollI.HandleCollision(enemyFireball[i], blocks[j]);
    }
    // for items
    for (size_t i = 0; i < enemies.size(); i++) {
        for (auto& fireball : *player->getFireBalls()) {
            CollI.HandleCollision(fireball, enemies[i]);
        }
        CollI.HandleCollision(player, enemies[i]);
    }
    for (size_t i = 0; i < items.size(); i++) {
        CollI.HandleCollision(player, items[i]);   
    }
    // enemy fireball
    for (size_t i = 0; i < enemyFireball.size(); i++) {
        CollI.HandleCollision(enemyFireball[i], player);
    }
}
// draw
void GameEngine::draw()
{
    camera.beginDrawing();
    ClearBackground(SKYBLUE);
    map.drawBackGround(camera.getSize(), camera.getScale());
    //map.drawMap();
    if (!player) return;
    bool lostLife = player->isLostLife();

    for (size_t i = 0; i < enemyFireball.size(); i++) {
        enemyFireball[i]->draw();
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->draw();
    }
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->draw();
    }
    for (size_t i = 0; i < items.size(); i++) {
        items[i]->draw();
    }

    player->draw();
    
    for (size_t i = 0; i < effects.size(); i++) {
        effects[i]->draw();
    }
    for (Entity* dec : decor) {
        dec->draw();
    }

    camera.endDrawing();

    BeginDrawing();

    camera.render();


    if (!lostLife) 
        GUI::drawStatusBar(player);

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
        if (player->isLostLife()) { // set animation & sound when dying
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
    for (size_t i = 0; i < enemyFireball.size(); i++) {
        delete enemyFireball[i];
    }
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
    for (size_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }

    enemyFireball.clear();
    blocks.clear();
    enemies.clear();
    items.clear();
    effects.clear();
    decor.clear();
    player->getFireBalls()->clear();
    map.clear();

    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    map.LoadFromJsonFile(level->getMapPath());
    map.loadBackgroundTexture(level->getBackGroundName());
    blocks = map.getBlocks();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();
    isPaused = false;
    this->time = 300;
    resetTimer();
}

Vector2 GameEngine::getBound()
{
    return map.getMapSize();
}

Character*& GameEngine::getCharacter()
{
    return player;
}

