#ifndef MAP_H
#define MAP_H
#include <raylib.h>
#include "../include/BlockFactory.h"
#include "../include/ItemFactory.h"
#include "../include/Blocks.h"
#include "../include/Floor.h"
#include "../include/SolidBlock.h"
#include "../include/Brick.h"
#include "../include/Cannon.h"
#include "../include/CoinBlock.h"
#include "../include/ItemBlock.h"
#include "../include/DecorBlock.h"
#include "../include/RotatingBlock.h"
#include "../include/NoteBlock.h"
#include "../include/HiddenBlock.h"
#include "../include/TemporaryBlock.h"
#include "../include/MovingBlock.h"
#include "../include/CloudBlock.h"
#include "../include/Item.h"
#include "../include/Goomba.h"
#include "../include/Koopa.h"
#include "../include/ParaKoopa.h"
#include "../include/PiranhaPlant.h"
#include "../include/JumpingPiranhaPlant.h"
#include "../include/FirePiranhaPlant.h"
#include "../include/Bullet.h"
#include "../include/BanzaiBill.h"
#include "../include/Rex.h"
#include "../include/Muncher.h"
#include "../include/BuzzyBeetle.h"
#include "../include/Spiny.h"

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
	float goalX; // for goal
	float goalY; // for goal
	std::string backGroundName;
	std::vector<MovingBlock*> movingBlocks; // for moving blocks
	std::vector<std::vector<Blocks*>> tileGrid; // for tile grid
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;
	std::vector<Blocks*> decors;
	std::vector<Blocks*> covers; //
	std::vector<Rectangle> secretAreas; // for secret areas
public:
	static const std::string basePath;
	Map();
	~Map();
	void clear();
	void drawMap();
	void drawBackGround();
	void drawBackGround(Vector2 cameraPos, float scale);
	Vector2 LoadMapSize(const std::string& filepath);
	void loadBackgroundTexture(const std::string& backgroundName);
	Vector2 getMapSize() const;
	Vector2 getGoalPosition() const;
	void setMapSize(Vector2 size);
	
	void LoadFromJsonFile(const std::string& filepath);
	bool LoadFromJsonFile(std::ifstream& file, std::vector<Blocks*>& blocks,
		std::vector<Enemy*>& enemies, std::vector<Item*>& items, std::vector<Blocks*>& decors);
	//bool stringToEnemyType(std::string& enemyTypeStr, std::string& subtype, ENEMY);

	//std::vector<Blocks*> getBlocks() const;
	std::vector<MovingBlock*> getMovingBlocks() const;
	std::vector<std::vector<Blocks*>> getTileGrid() const;
	std::vector<Enemy*> getEnemies() const;
	std::vector<Item*> getItems() const; 
	std::vector<Blocks*> getDecor() const;
	std::vector<Blocks*> getCovers() const;
	std::vector<Rectangle> getSecretAreas() const;

	float BgWidth;
	float BgHeight;
	void loadMap(const json& j);
	void saveMap(json& j) const;
};
#endif