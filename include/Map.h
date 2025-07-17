#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/Blocks.h"
#include "../include/Floor.h"
#include "../include/SolidBlock.h"
#include "../include/Brick.h"
#include "../include/CoinBlock.h"
#include "../include/ItemBlock.h"
#include "../include/Item.h"
#include "../include/Goomba.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"
#include <string>
#include <map>
#include "../include/ResourceManager.h"

using json = nlohmann::json; // to load file json

class Enemy;

class Map {
private:
	Texture2D background;
	std::map<std::string, Texture2D> backgroundTextures;
	std::vector<Vector2> BackGroundPos;
	float width;
	float height;

	std::vector<Blocks*> blockArray; // replace tile
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;
	std::vector<Blocks*> decors;
	
public:
	static const std::string basePath;
	Map();
	~Map();
	void clear();
	void drawMap();
	void drawBackGround();
	void drawBackGround(Vector2 cameraPos, float scale);
	void loadBackgroundTexture(const std::string& backgroundName);
	Vector2 getMapSize() const;
	void setMapSize(Vector2 size);

	void LoadFromJsonFile(const std::string& filepath);
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