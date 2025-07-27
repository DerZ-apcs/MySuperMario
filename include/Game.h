#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
#include "../include/Clock.h"
#include "../include/ResourceManager.h"
#include "../include/Tile.h"
#include "../include/Map.h"
#include "../include/MediatorCollision.h"
#include "../include/Enemy.h"
#include "../include/Goomba.h"
#include "../include/Koopa.h"
#include "../include/Bullet.h"
#include "../include/PiranhaPlant.h"
#include "../include/Rex.h"
#include "../include/FirePiranhaPlant.h"
#include "../include/Muncher.h"
#include "../include/BobOmb.h"
#include "../include/ParaKoopa.h"
#include "../include/JumpingPiranhaPlant.h"
#include "../include/DryBones.h"

class Game {
private:
	int width;
	int height;
	int targetFPS;
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
	std::vector<Enemy*> enemies;
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

	void setWidth(int width);
	void setHeight(int height);
	void setTargetFPS(int targetFPS);

	Mario* getMario() {
		return &mario;
	}
};

#endif