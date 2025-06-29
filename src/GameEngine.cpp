#include "../include/GameEngine.h"
#include <iostream>

GameEngine* globalGameEngine = nullptr;

GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, Mario*& player)
    : camera(screenWidth, screenHeight, 1.75f), level(&level), player(player) {
    map.LoadFromJsonFile(level.getMapPath());
    map.loadBackgroundTexture(level.getBackGroundName());
    Vector2 Msize = map.getMapSize();
    camera.loadRenderTexture(Msize);
    /*blocks = map.getBlocks();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();*/
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
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

void GameEngine::update(float deltaTime) {

}

// run
bool GameEngine::run() {
    bool flag = true;
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic("MUSIC1"); // temporary
    // load and play the new music

    // second game loop (main game loop)
    while (!WindowShouldClose()) {
        
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
}

Vector2 GameEngine::getBound()
{
    return map.getMapSize();
}

