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

void saveMultiCharacters(const std::vector<std::unique_ptr<Character>>& multiplayers, json& j);
void loadMultiCharacters(std::vector<std::unique_ptr<Character>>& multiplayers, const json& j);

void saveEnemies(const std::vector<Enemy*>& enemies, json& j);
void loadEnemies(std::vector<Enemy*>& enemies, const json& j);

void saveItems(const std::vector<Item*>& items, json& j);
void loadItems(std::vector<Item*>& items, const json& j);

void saveTileGrids(const std::vector<std::vector<Blocks*>>& tileGrid, json& j);
void loadTileGrids(std::vector<std::vector<Blocks*>>& tileGrid, const json& j);

bool isBasisBlock(BLOCK_TYPE type);