#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "../include/Camera.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"
#include "../include/FireBall.h"
#include "../include/Map.h"
#include "../include/GUI.h"
#include "../include/Item.h"
#include "../include/Blocks.h"
#include "../include/CollisionInfo.h"
#include <vector>
#include <string>
#include <map>

class Enemy;
class Effect;
class Level;

class GameEngine {
private:
    struct PlayerControls {
        int left, right, up, down, fire;
    };
    std::vector<PlayerControls> controlBindings = {
        {KEY_A, KEY_D, KEY_W, KEY_S, KEY_LEFT_SHIFT},
        {KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_RIGHT_SHIFT}
    };
    Level* level;
    Map map;
    /*Character* player;
    Character* player2 = nullptr;*/
    std::vector<Character*> multiplayers; // for multiplayers
    std::vector<Blocks*> blocks;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::vector<EnemyFireBall*> enemyFireball;
    std::vector<Effect*> effects;
    std::vector<Blocks*> decor;
    std::vector<Entity*> testEntities;
    GameCamera camera;
    bool isvictory = false;
    bool died = false;
    bool gameover = false;
    bool isPaused;
    bool cleared = false;
    float time;
    float deltaTime;
    int sharedLives = 5;
    Texture2D BackGroundTex;

    std::map<std::string, Texture2D> backgroundTextures;
    std::vector<Vector2> BackGroundPos;

public:
    GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player);
    GameEngine(float screenWidth, float screenHeight, Level& level, std::vector<Character*>& multiplayers);
    ~GameEngine();
    void addScore(int amount);
    void addEnemyFireBall(EnemyFireBall* fireball);
    void addEnemy(Enemy* enemy);
    void addEffect(Effect* effect);
    void addItem(Item* item);
    void update();
    void handleCollision();
    void draw(); // draw
    bool run();
    string getCurrentMapName();
    float getGlobalTime() const;
    float getRemainingTime() const;
    float resetTimer();
    bool isOver() const;
    void resetGame();
    Vector2 getBound();
    std::vector<Character*>& getMultiplayers();
};
extern GameEngine* globalGameEngine;

#endif