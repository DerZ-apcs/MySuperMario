#include "../include/Menu.h"

MainMenuState::MainMenuState(Game* game)
{
	this->game = game;
	startButton = { {80, 720}, {0, 0}, ORANGE, DARKGRAY, "Start" };
	continueButton = { {340, 720}, {160, 40}, ORANGE, DARKGRAY, "Continue" };
	settingButton = { {700, 720}, {160, 40}, ORANGE, DARKGRAY, "Setting" };
	charSelectionButton = { {1000, 720}, {200, 40}, ORANGE, DARKGRAY, "Character" };
	mapSelectionButton = { {1390, 720}, {160, 40}, ORANGE, DARKGRAY, "Map" };
}

void MainMenuState::draw()
{
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	charSelectionButton.draw();
	mapSelectionButton.draw();
}

void MainMenuState::handleInput()
{
	//if (continueButton.isPressed()) {
	//	
	//} 
	//else if (startButton.isPressed()) {
	//	if (game->player) {
	//		game->player->reset();
	//	}
	//}
}

void MainMenuState::update()
{
	startButton.update();
	continueButton.update();
	settingButton.update();
	charSelectionButton.update();
	mapSelectionButton.update();
}

MainMenuState::~MainMenuState()
{
	RESOURCE_MANAGER.UnloadAllResources();
}

// SettingState implementation
SettingState::SettingState(Game* game) { 
	this->game = game; 
}


void SettingState::draw()
{
}

void SettingState::handleInput()
{
}

//CharSlection implementation
CharSelection::CharSelection(Game* game) 
{ 
	this->game = game; 
}


void CharSelection::draw()
{
}

void CharSelection::handleInput()
{
}

//MapSelection Implementation

MapSelection::MapSelection(Game* game)
{
	this->game = game;
}

void MapSelection::draw()
{
}

void MapSelection::handleInput()
{
}

