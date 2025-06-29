#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"
using json = nlohmann::json; // to load file json

class Map {
private:
	std::vector<Tile*> tiles;
	Texture2D background;
	float width;
	float height;
public:
	static const std::string basePath;
	Map();
	~Map();
	std::string TileTypeToString(TileType type);
	TileType StringToTileType(const std::string& str);
	std::vector<Tile*> *getVectorTiles();
	void AddTile(Vector2 pos, TileType type, const std::string& name);
	void clear();
	void drawMap();
	void LoadFromJsonFile(const std::string& filepath);
	void loadBackgroundTexture(const std::string& backgroundName);
	Vector2 getMapSize() const;
	void setMapSize(Vector2 size);
};
#endif