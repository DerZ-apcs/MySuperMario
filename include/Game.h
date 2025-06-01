#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "../include/Mario.h"
#include "../include/Clock.h"
#include "../include/ResourceManager.h"
#include "../include/Tile.h"
#include "../include/Map.h"
#include "../include/MediatorCollision.h"

class Game {
private:
	int width;
	int height;
	int targetFPS;
	//Color color;
	//Camera2D camera;

	//bool initialize;
	std::vector<Tile*> Tiles;
	Mario mario;
	Map map1;
	Texture2D BackGroundTex;
	MediatorCollision mediatorCollision;
	ResourceManager& Resource_manager;
	float BgWidth;
	float BgHeight;
	std::vector<Vector2> BackGroundPos;
	Camera2D camera;
public:
	Game();
	Game(int nwidth, int nheight, int ntargetFPS);
	~Game();

	void initGame();
	void UpdateGame();
	void draw();
	void drawBackGround() const;

	int getWidth() const;
	int getHeight() const;
	int getTergetFPS() const;
	//Color getColor();

	void setWidth(int width);
	void setHeight(int height);
	void setTargetFPS(int targetFPS);
	//void setColor(Color color);
};
#endif