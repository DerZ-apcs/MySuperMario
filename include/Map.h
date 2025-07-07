#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Blocks.h"
#include "../include/Item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"
#include <string>
#include <map>

using json = nlohmann::json; // to load file json

class Enemy;

class Map {
private:
	std::vector<Tile*> tiles;
	Texture2D background;
	std::map<std::string, Texture2D> backgroundTextures;
	std::vector<Vector2> BackGroundPos;
	float width;
	float height;

	std::vector<Blocks*> blockArray;
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;
	std::vector<Blocks*> decors;
	
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
	void drawBackGround();
	void drawBackGround(Vector2 cameraPos, float scale);
	void LoadFromJsonFile(const std::string& filepath);
	void loadBackgroundTexture(const std::string& backgroundName);
	Vector2 getMapSize() const;
	void setMapSize(Vector2 size);

	bool LoadFromJsonFile(std::ifstream& file, std::vector<Blocks*>& blocks,
		std::vector<Enemy*>& enemies, std::vector<Item*>& items, std::vector<Blocks*>& decors);
	//bool stringToEnemyType(std::string& enemyTypeStr, std::string& subtype, ENEMY);

	std::vector<Blocks*> getBlocks() const;
	std::vector<Enemy*> getEnemies() const;
	std::vector<Item*> getItems() const;
	std::vector<Blocks*> getDecor() const;

	float BgWidth;
	float BgHeight;
};
#endif