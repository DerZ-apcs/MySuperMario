#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "../include/Camera.h"
#include "../include/Mario.h"
#include "../include/FireBall.h"
#include "../include/Map.h"
#include "../include/GUI.h"
#include "../include/Item.h"
#include "../include/Blocks.h"
#include "../include/MediatorCollision.h"
//#include "../include/Effect.h"
//#include "../include/Enemy.h"
#include <vector>
#include <string>
#include <map>

class Enemy;
class Effect;
class Level;

class GameEngine {
private:
    Level* level;
    Map map;
    Character* player;
    std::vector<Blocks*> blocks;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::vector<FireBall*> fireball;
    std::vector<Effect*> effects;
    std::vector<Blocks*> decor;
    //std::vector<Shell*> shells;
    std::vector<Entity*> testEntities;
    GameCamera camera;
    bool isvictory = false;
    bool died = false;
    bool gameover = false;
    bool isPaused;
    bool cleared = false;
    float time;
    float deltaTime;
    Texture2D BackGroundTex;

    std::vector<Tile*> Tiles;
    std::map<std::string, Texture2D> backgroundTextures;
    std::vector<Vector2> BackGroundPos;
    MediatorCollision mediatorCollision;

public:
    GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player);
    ~GameEngine();
    void resolveCollision();
    void addScore(int amount);
    void addFireBall(FireBall* fireball);
    void addEnemy(Enemy* enemy);
    void addEffect(Effect* effect);
    //void addShell(Shell* shell);
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
};
extern GameEngine* globalGameEngine;

#endif