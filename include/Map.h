#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"
using json = nlohmann::json;

class Map {
private:
	std::vector<Tile*> tiles;
public:
	static const std::string basePath;
	Map();
	~Map();
	std::string TileTypeToString(TileType type);
	TileType StringToTileType(const std::string& str);
	std::vector<Tile*> *getVectorTiles();
	void AddTile(Vector2 pos, TileType type, const std::string& name);
	void saveToFile(const std::string& filename);
	void loadFromFile(const std::string& filename);
	void clear();
	void drawMap();
	void LoadFromJsonFile(const std::string& filepath);
};
#endif