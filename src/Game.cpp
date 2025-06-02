#include "../include/Game.h"
#include "../include/Map.h"
#include <iostream>

Game::Game(): Game(1200, 800, 140)
{
}

Game::Game(int nwidth, int nheight, int ntargetFPS) :
	width(nwidth), height(nheight), targetFPS(ntargetFPS) {
	RESOURCE_MANAGER.LoadAllResources();
	// map
	//map1.LoadFromJsonFile(Map::basePath + "MAP_1.1.json");
	// background
	BgWidth = (float)GetScreenWidth();
	BgHeight = (float)GetScreenHeight();
	//BackGroundTex = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	BackGroundPos = {{0, 0}, {BgWidth, 0}, {BgWidth*2, 0}};
	// camera
	/*camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	camera.target = mario.getPosition();
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;*/
	
	backgroundTextures["MENUSCREEN"] = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	backgroundTextures["BACKGROUND_1"] = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	BackGroundTex = backgroundTextures["MENUSCREEN"];
	startButton = { {80, 720}, {0, 0}, ORANGE, DARKGRAY, "Start"};
	continueButton = { {340, 720}, {160, 40}, ORANGE, DARKGRAY, "Continue" };
	settingButton = { {700, 720}, {160, 40}, ORANGE, DARKGRAY, "Setting" };
	charSelectionButton = { {1000, 720}, {200, 40}, ORANGE, DARKGRAY, "Character" };
	mapSelectionButton = { {1390, 720}, {160, 40}, ORANGE, DARKGRAY, "Map" };
}

Game::~Game()
{
	Singleton<ResourceManager>::getInstance().UnloadAllResources();

}

void Game::initGame()
{
	SetTargetFPS(targetFPS);
	//RESOURCE_MANAGER.playMusic("TITLE");

	while (!WindowShouldClose()) {
		UpdateGame();
		UpdateMusicStream(RESOURCE_MANAGER.getMusic("TITLE"));
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
	if (mario.getX() >= GetScreenWidth() / 2.0f ) {
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
	// tiles
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
	
	//mario.Update();
	startButton.update();
	continueButton.update();
	settingButton.update();
	charSelectionButton.update();
	mapSelectionButton.update();
}

void Game::draw()
{

	//BeginMode2D(camera);
	drawBackGround();
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	charSelectionButton.draw();
	mapSelectionButton.draw();
	//mario.draw();
	//map1.drawMap();
	//EndMode2D();
}

void Game::drawBackGround() 
{
	//ClearBackground(SKYBLUE);
	DrawTexturePro(BackGroundTex, { 0, 0, (float)BackGroundTex.width, (float)BackGroundTex.height },
		{ BackGroundPos[0].x, BackGroundPos[0].y, BgWidth, BgHeight},
		{ 0, 0 }, 0.0f, WHITE);
	/*for (int i = 0; i < 3; i++) {
		DrawTexturePro(BackGroundTex, { 0, 0, (float)BackGroundTex.width, (float)BackGroundTex.height },
			{ BackGroundPos[i].x, BackGroundPos[i].y, BgWidth, BgHeight },
			{ 0, 0 }, 0.0f, WHITE);
	}*/
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