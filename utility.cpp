
//class Game {
//private:
//	int width;
//	int height;
//	int targetFPS;
//
//	std::vector<Tile*> Tiles;
//
//	Texture2D BackGroundTex;
//	std::map<string, Texture2D> backgroundTextures;
//	MediatorCollision mediatorCollision;
//	float BgWidth;
//	float BgHeight;
//	std::vector<Vector2> BackGroundPos;
//	Camera2D camera;
//	std::vector<Button> Buttons;
//
//public:
//	Game();
//	Game(int nwidth, int nheight, int ntargetFPS);
//	~Game();
//
//	void initGame();
//	void UpdateGame();
//	void draw();
//	void drawBackGround();
//
//	int getWidth() const;
//	int getHeight() const;
//	int getTergetFPS() const;
//	//Color getColor();
//
//	void setWidth(int width);
//	void setHeight(int height);
//	void setTargetFPS(int targetFPS);
//	//void setColor(Color color);
//	Mario mario;
//	Map map1;
//};
//#endif

#include "../include/Game.h"
#include "../include/Map.h"
#include <iostream>

Game* globalGame = nullptr;

Game::Game() : Game(1200, 800, 140)
{
}

Game::Game(int nwidth, int nheight, int ntargetFPS) :
	width(nwidth), height(nheight), targetFPS(ntargetFPS) {
	RESOURCE_MANAGER.LoadAllResources();
	// map
	map1.LoadFromJsonFile(Map::basePath + "MAP_1.1.json");
	// background
	BgWidth = (float)GetScreenWidth();
	BgHeight = (float)GetScreenHeight();
	BackGroundTex = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	BackGroundPos = { {0, 0}, {BgWidth, 0}, {BgWidth * 2, 0} };
	// camera
	camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	camera.target = mario.getPosition();
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	backgroundTextures["MENUSCREEN"] = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	backgroundTextures["BACKGROUND_1"] = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	BackGroundTex = backgroundTextures["BACKGROUND_1"];

}

Game::~Game()
{
	RESOURCE_MANAGER.UnloadAllResources();

}

void Game::initGame()
{
	SetTargetFPS(targetFPS);
	RESOURCE_MANAGER.playMusic("MUSIC1");
	// main while loop
	while (!WindowShouldClose()) {
		UpdateGame();
		UpdateMusicStream(RESOURCE_MANAGER.getMusic("MUSIC1"));
		ClearBackground(RAYWHITE);
		BeginDrawing();
		draw();
		EndDrawing();
	}
}

void Game::UpdateGame()
{
	// cemera & background
	camera.target.y = GetScreenHeight() / 2.0f;
	if (mario.getX() >= GetScreenWidth() / 2.0f) {
		camera.target.x = mario.getX();
	}
	else camera.target.x = GetScreenWidth() / 2.0f;

	for (int i = 0; i < 3; i++) {
		// wrap from left to far most right
		if (BackGroundPos[i].x + BgWidth <= mario.getX() - BgWidth / 2.0f) {
			float maxX = BackGroundPos[0].x;
			for (int j = 1; j < 3; j++) {
				if (BackGroundPos[j].x > maxX) maxX = BackGroundPos[j].x;
			}
			BackGroundPos[i].x = maxX + BgWidth;
		}
		// wrap from right to left
		if (BackGroundPos[i].x + BgWidth / 2.0f >= mario.getX() + BgWidth * 2) {
			float minX = BackGroundPos[i].x;
			for (int j = 1; j < 3; j++) {
				if (BackGroundPos[j].x < minX) minX = BackGroundPos[j].x;
			}
			BackGroundPos[i].x = minX - BgWidth;
		}

	}
	// tiles (collision with character)
	for (auto const& tile : *map1.getVectorTiles()) {
		CollisionType PlayerCollision = mario.CheckCollision(*tile);
		if (PlayerCollision != COLLISION_TYPE_NONE)
			mediatorCollision.HandleCollision(&mario, tile);
		//mario.HandleTileCollision(*tile, MarioCollision);
		for (auto& fireball : *mario.getFireBalls()) {
			CollisionType FireBallCollision = fireball->CheckCollision(*tile);
			if (FireBallCollision != COLLISION_TYPE_NONE)
				mediatorCollision.HandleCollision(fireball, tile);
			//fireball->HandleTileCollision(*tile, FireBallCollision);
		}
	}

	mario.Update();
}

void Game::draw()
{

	BeginMode2D(camera);
	drawBackGround();
	mario.draw();
	map1.drawMap();
	EndMode2D();
}

void Game::drawBackGround()
{
	ClearBackground(SKYBLUE);
	for (int i = 0; i < 3; i++) {
		DrawTexturePro(BackGroundTex, { 0, 0, (float)BackGroundTex.width, (float)BackGroundTex.height },
			{ BackGroundPos[i].x, BackGroundPos[i].y, BgWidth, BgHeight },
			{ 0, 0 }, 0.0f, WHITE);
	}
}


int Game::getWidth() const {
	return width;
}
int Game::getHeight() const {
	return height;
}
int Game::getTergetFPS() const {
	return targetFPS;
}
void Game::setWidth(int width) {
	this->width = width;
}
void Game::setHeight(int height) {
	this->height = height;
}
void Game::setTargetFPS(int targetFPS) {
	this->targetFPS = targetFPS;
}