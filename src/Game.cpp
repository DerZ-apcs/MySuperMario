#include "../include/Game.h"
#include <iostream>
Game::Game() {
	
}

Game::Game(int nwidth, int nheight, int ntargetFPS) :
	width(nwidth), height(nheight), targetFPS(ntargetFPS) { }

void Game::init()
{
	/*std::cout << "Starting Mario Game" << std::endl;
	InitWindow(width, height, "MySuperMario");
	SetTargetFPS(targetFPS);
	while (!WindowShouldClose()) {

	}*/
}

int Game::getWidth() {
	return width;
}
int Game::getHeight() {
	return height;
}
int Game::getTergetFPS() {
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