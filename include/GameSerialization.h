#pragma once
#include "../include/json.hpp"
#include "../include/Character.h"
#include "../include/Enemy.h"
#include "../include/Item.h"
#include "../include/Luigi.h"
#include "../include/Peach.h"
#include "../include/Marisa.h"
#include "../include/Toad.h"
#include "../include/EnemyFireBall.h"
#include "../include/Blocks.h"

using json = nlohmann::json;

void to_json(json& j, const Character& c);
void to_json(json& j, const Enemy& e);
void to_json(json& j, const Item& item);
void to_json(json& j, const Blocks& b);
void to_json(json& j, const FireBall& fb);
void to_json(json& j, const EnemyFireBall& ef);
void to_json(json& j, const int remainedTime, const int level);

std::unique_ptr<Character> loadCharacter(const json& j);
Enemy* loadEnemy(const json& j);
Item* loadItem(const json& j);
Blocks* loadBlocks(const json& j);
FireBall loadFireBall(const json& j);
EnemyFireBall loadEnemyFireBall(const json& j);

void saveMultiCharacters(const std::vector<std::unique_ptr<Character>>& multiplayers, json& j);
void loadMultiCharacters(std::vector<std::unique_ptr<Character>>& multiplayers, const json& j);

void saveEnemies(const std::vector<Enemy*>& enemies, json& j);
void loadEnemies(std::vector<Enemy*>& enemies, const json& j);

void saveItems(const std::vector<Item*> items, json& j);
void loadItems(std::vector<Item*>& items, const json& j);

void saveTileGrids(const std::vector<std::vector<Blocks*>> tileGrid, json& j);
void loadTileGrids(std::vector<std::vector<Blocks*>>& tileGrid, const json& j);

void saveEffects(const std::vector<Effect> effects, json& j);
void loadEffects(std::vector<Effect>& effects, const json& j);

void saveFireBall(const std::vector<FireBall> fireballs, json& j);
void loadFireBall(std::vector<FireBall>& fireballs, const json& j);

void saveEnemyFireBall(const std::vector<FireBall> enemyfireballs, json& j);
void loadEnemyFireBall(std::vector<FireBall>& enemyfireballs, const json& j);

void saveDecor(const std::vector<Blocks> decors, json& j);
void loadDecor(std::vector<Blocks>& decors, const json& j);

void saveCover(const std::vector<Blocks> covers, json& j);
void loadCover(std::vector<Blocks>& covers, const json& j);

void saveSecretArea(const std::vector<Rectangle> secret, json& j);
void loadSecretArea(std::vector<Rectangle>& scret, const json& j);

void saveGameState(const int Remainedtime, const int level, json& j);
void loadGameState(int& Remainedtime, int& level, const json& j);

static Texture2D loadTextureFromType(ENEMY_TYPE type);
