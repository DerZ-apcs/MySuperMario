#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "../include/Mario.h"
#include "../include/Clock.h"
#include "../include/ResourceManager.h"
#include "../include/Tile.h"
#include "../include/Map.h"

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
	Camera2D camera;
public:
	Game();
	Game(int nwidth, int nheight, int ntargetFPS);
	~Game();

	void initGame();
	void UpdateGame();
	void draw();

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