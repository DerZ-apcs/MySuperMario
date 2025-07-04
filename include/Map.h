#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Coin.h"
#include "../include/Brick.h"
#include "../include/QuestionBlock.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"
using json = nlohmann::json; // to load file json

class Map {
private:
	std::vector<Tile*> tiles;
	std::vector<Coin*> coins;
public:
	static const std::string basePath;
	Map();
	~Map();
	std::string TileTypeToString(TileType type);
	TileType StringToTileType(const std::string& str);
	std::vector<Tile*> *getVectorTiles();
	std::vector<Coin*> *getVectorCoins();
	void AddTile(Vector2 pos, TileType type, const std::string& name);
	void loadFromFile(const std::string& filename);
	void clear();
	void drawMap();
	void LoadFromJsonFile(const std::string& filepath);

	
};
#endif