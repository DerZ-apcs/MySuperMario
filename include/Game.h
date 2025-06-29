#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "../include/Mario.h"
#include "../include/Clock.h"
#include "../include/ResourceManager.h"
#include "../include/Global.h"
#include "../include/Tile.h"
#include "../include/Map.h"
#include "../include/MediatorCollision.h"
#include "../include/Menu.h"

class Game {
private:
	int width;
	int height;
	int targetFPS;
	
	std::vector<Tile*> Tiles;

	Texture2D BackGroundTex;
	std::map<string, Texture2D> backgroundTextures;
	MediatorCollision mediatorCollision;
	float BgWidth;
	float BgHeight;
	std::vector<Vector2> BackGroundPos;
	Camera2D camera;
	std::vector<Button> Buttons;

public:
	Game();
	Game(int nwidth, int nheight, int ntargetFPS);
	~Game();

	void initGame();
	void UpdateGame();
	void draw();
	void drawBackGround();

	int getWidth() const;
	int getHeight() const;
	int getTergetFPS() const;
	//Color getColor();

	void setWidth(int width);
	void setHeight(int height);
	void setTargetFPS(int targetFPS);
	//void setColor(Color color);
	Mario mario;
	Map map1;
};
#endif