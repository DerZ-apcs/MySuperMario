#include "../include/Menu.h"
#include "../include/Game.h"

MainMenuState::MainMenuState(Game* game)
{
	this->game = game;
	startButton = { Vector2{80, 720}, Vector2{160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Start" };
	continueButton = { {340, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Continue" };
	settingButton = { {700, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Setting" };
	charSelectionButton = { {1000, 720}, {200, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Character" };
	mapSelectionButton = { {1390, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Map" };
}

void MainMenuState::draw()
{
	startButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	continueButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	mapSelectionButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	charSelectionButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	settingButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	charSelectionButton.draw();
	mapSelectionButton.draw();
}

void MainMenuState::handleInput()
{
	if (continueButton.isPressed()) {
		if (globalGameEngine == nullptr) {
			if (game->player == nullptr)
				game->player = new Mario();
			game->player->setPosition({ 32, 400 });
			game->player->setVel({ 0, 0 });
			game->player->setState(FALLING);
			GameEngine* gameEngine = new GameEngine(1600, 800, *game->level, game->player);
			globalGameEngine = gameEngine;
		}
		while (globalGameEngine != nullptr) {
			if (globalGameEngine->run()) {
				delete globalGameEngine;
				globalGameEngine = nullptr;
				if ((game->getSelectedMap() + 1) <= 4)
				{
					if (game->player == nullptr)
						game->player = new Mario();
					game->player->setPosition({ 32, 400 });
					game->player->setVel({ 0,0 });
					game->player->setState(FALLING);
					game->selectMap(game->getSelectedMap() + 1);
					GameEngine* gameEngine = new GameEngine(820.0f, 512.0f, *game->level, game->player);
					globalGameEngine = gameEngine;
				}
				else break;
			}
			else {
				if (globalGameEngine->isOver())
					game->player->reset();
				break;
			}
		}
	}
	else if (startButton.isPressed()) {
		if (game->player == nullptr)
			game->player = new Mario();
		if (game->player) {
			game->player->reset();
		}
		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		GameEngine* gameEngine = new GameEngine(1600, 800, *game->level, game->player);
		globalGameEngine = gameEngine;
		
		while (globalGameEngine != nullptr) {
			if (globalGameEngine->run()) {
				delete globalGameEngine;
				globalGameEngine = nullptr;

				if ((game->getSelectedMap() + 1) <= 4) {
					game->player->setPosition({ 16, 400 });
					game->player->setVel({ 0, 0 });
					game->selectMap(game->getSelectedMap() + 1);
					game->player->setState(FALLING);
					GameEngine* gameEngine = new GameEngine(1600, 800, *game->level, game->player);
					globalGameEngine = gameEngine;
				}
				else break;
			}
			else {
				if (globalGameEngine->isOver())
					game->player->reset();
				break;
			}
		}
	}
	else if (settingButton.isPressed())
		game->setState(std::make_unique<SettingState>(game));
	else if (charSelectionButton.isPressed())
		game->setState(std::make_unique<CharSelection>(game));
	else if (mapSelectionButton.isPressed())
		game->setState(std::make_unique<MapSelection>(game));
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

}

// SettingState implementation
SettingState::SettingState(Game* game) { 
	this->game = game; 
	audioButton = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Audio: ON" };
	musicButton = { {500, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Music: ON" };
	backButton = { {900, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Return to Main Menu" };
}


void SettingState::draw()
{
	audioButton.draw();
	musicButton.draw();
	backButton.draw();
}

void SettingState::handleInput()
{
	if (audioButton.isPressed()) {
		if (SETTING.isSoundEnabled())
			audioButton.setText("Sound: OFF");
		else audioButton.setText("Sound: ON");
		SETTING.setSound(!game->isAudioEnabled());
		game->configureSettings(!game->isAudioEnabled(), game->isMusicEnabled());
	} 
	else if (musicButton.isPressed()) {
		if (SETTING.isMusicEnabled())
			musicButton.setText("Music: OFF");
		else musicButton.setText("Music: ON");
		SETTING.setMusic(!game->isMusicEnabled());
		game->configureSettings(game->isAudioEnabled(), !game->isMusicEnabled());
	}
	else if (backButton.isPressed()) {
		game->returnToMainMenu();
	}
}

void SettingState::update()
{
	audioButton.update();
	musicButton.update();
	backButton.update();

	if (SETTING.isMusicEnabled() && musicButton.getText() == "Music: OFF")
		musicButton.setText("Music: ON");
	else if (!SETTING.isMusicEnabled() && musicButton.getText() == "Music: ON")
		musicButton.setText("Music: OFF");
	/*SETTING.setMusic(!game->isMusicEnabled());
	game->configureSettings(game->isAudioEnabled(), !game->isMusicEnabled());*/
}

//CharSlection implementation
CharSelection::CharSelection(Game* game) 
{ 
	this->game = game; 
	MarioButton = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Mario" };
	LuigiButton = { {500, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Luigi" };
	backButton = { {900, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Return to Main Menu" };
}


void CharSelection::draw()
{
	MarioButton.draw();
	LuigiButton.draw();
	backButton.draw();

}

void CharSelection::handleInput()
{
	if (MarioButton.isPressed()) {
		if (game->player) delete game->player;
		game->player = new Mario();
		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
	else if (LuigiButton.isPressed()) {
		if (game->player) delete game->player;
		game->player = new Luigi(); // new Luigi 
		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
	else if (backButton.isPressed())
		game->returnToMainMenu();
}

void CharSelection::update()
{
	MarioButton.update();
	LuigiButton.update();
	backButton.update();
}

//MapSelection Implementation

MapSelection::MapSelection(Game* game)
{
	this->game = game;
	map1Button = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "MAP 1" };
	map2Button = { {400, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "MAP 2" };
	map3Button = { {700, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "MAP 3" };
	backButton = { {1000, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Return to Main Menu" };
}

void MapSelection::draw()
{
	map1Button.draw();
	map2Button.draw();
	map3Button.draw();
	backButton.draw();
}

void MapSelection::handleInput()
{
	if (map1Button.isPressed()) {
		game->selectMap(1);
		game->player->reset();
		game->returnToMainMenu();
	}
	else if (map2Button.isPressed()) {
		game->selectMap(2);
		game->player->reset();
		game->returnToMainMenu();
	}
	else if (map3Button.isPressed()) {
		game->selectMap(3);
		game->player->reset();
		game->returnToMainMenu();
	}
	else if (backButton.isPressed())
		game->returnToMainMenu();
}

void MapSelection::update()
{
	map1Button.update();
	map2Button.update();
	map3Button.update();
	backButton.update();
}

