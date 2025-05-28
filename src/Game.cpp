#include "../include/Game.h"
#include <iostream>

Game::Game(): Game(1200, 800, 140)
{
}

Game::Game(int nwidth, int nheight, int ntargetFPS) :
	width(nwidth), height(nheight), targetFPS(ntargetFPS) { 
	ResourceManager::LoadAllResources();

	//camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	//camera.target = mario.getPosition();
	//camera.rotation = 0.0f;
	//camera.zoom = 0.0f;

	Tiles.push_back(new Tile(Vector2{ 0, 500 }, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
	for (int i = 1;i < 10;i++)
	{
		Tiles.push_back(new Tile(Vector2{ (float)i * 32, 500 }, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
		Tiles.push_back(new Tile(Vector2{ (float)i * 32, 300 }, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
	}

	Tiles.push_back(new Tile(Vector2{ 10 * 32, 500 }, TileType::TILE_TYPE_LEFT_EDGE, "MAP1_GRASS"));
	Tiles.push_back(new Tile(Vector2{ 11 * 32, 500 }, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
	for (int i = 12;i < 25;i++)
	{
		Tiles.push_back(new Tile(Vector2{ (float)i * 32, 500 }, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
		Tiles.push_back(new Tile(Vector2{ (float)i * 32 + 64, 700 }, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
	}
}

Game::~Game()
{
	ResourceManager::UnloadAllResources();
	for (auto& tile : Tiles) {
		delete tile;
		tile = nullptr;
	}
	Tiles.clear();
}

void Game::initGame()
{
	SetTargetFPS(targetFPS);
	while (!WindowShouldClose()) {
		UpdateGame();
		ClearBackground(RAYWHITE);
		BeginDrawing();
		draw();
		EndDrawing();
	}
}

void Game::UpdateGame()
{
	//camera.target = mario.getPosition();
	for (auto const& tile : Tiles) {
		CollisionType MarioCollision = mario.CheckCollision(tile);
		mario.HandleTileCollision(*tile, MarioCollision);
	}
	mario.Update();
}

void Game::draw()
{
	//BeginMode2D(camera);
	mario.draw();
	for (auto& tile : Tiles) {
		tile->draw();
	}
	//EndMode2D();
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
//Color Game::getColor() {
//	return this->color;
//}

void Game::setWidth(int width) {
	this->width = width;
}
void Game::setHeight(int height) {
	this->height = height;
}
void Game::setTargetFPS(int targetFPS) {
	this->targetFPS = targetFPS;
}
//void Game::setColor(Color color) {
//	this->color = color;
//}