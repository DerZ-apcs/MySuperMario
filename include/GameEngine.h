#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "../include/Camera.h"
#include "../include/Mario.h"
#include "../include/FireBall.h"
#include "../include/Map.h"
#include "../include/Level.h"
#include "../include/MediatorCollision.h"
#include <vector>


class GameEngine {
private:
    Level* level;
    Map map;
    Mario* player;
    /*std::vector<BaseBlock*> blocks;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;*/
    std::vector<FireBall*> fireball;
   /* std::vector<Effect*> effects;
    std::vector<BaseBlock*> decor;
    std::vector<Shell*> shells;*/
    std::vector<Entity*> testEntities;
    GameCamera camera;
    bool isPaused;
    bool cleared = false;
    bool died = false;
    bool gameover = false;
    float time;
    float deltaTime;
    std::vector<Tile*> Tiles;
    Texture2D BackGroundTex;
    std::map<string, Texture2D> backgroundTextures;
    MediatorCollision mediatorCollision;
    //Camera2D camera;

public:
    GameEngine(float screenWidth, float screenHeight, Level& level, Mario*& player);
    ~GameEngine();
    void resolveCollision();
    void addScore(int amount);
    void addFireBall(FireBall* fireball);
    //void addEnemy(Enemy* enemy);
    /*void addEffect(Effect* effect);
    void addShell(Shell* shell);
    void addItem(Item* item);*/
    void update(float deltaTime);
    void handleCollision();
    void render(float deltaTime);
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