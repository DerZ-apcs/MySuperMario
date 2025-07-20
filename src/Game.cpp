#include "../include/Game.h"
#include "../include/Level.h"
#include "../include/ItemFactory.h"
#include "../include/BlockManagement.h"

class MenuState;

Game::Game(): backgroundTexture({0})
{
	currentState = std::make_unique<MainMenuState>(this);
	audioEnabled = true;
	musicEnabled = true;
	level = nullptr;
	selectedCharacter = 1;
	selectedMap = 1;
}

Game::~Game()
{
	if (backgroundTexture.id != 0) {
		UnloadTexture(backgroundTexture);
		backgroundTexture.id = 0;
	}
}

void Game::init()
{
	InitAudioDevice();
	InitWindow(1600, 800, "Super Mario");
	// game icon
	Texture gameIcon = LoadTexture("resources/images/icon/GameIcon.png");
	Image gameIconImage = LoadImageFromTexture(gameIcon);
	SetWindowIcon(gameIconImage);

	RESOURCE_MANAGER.LoadAllResources();
	if (backgroundTexture.id == 0) {
		backgroundTexture = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	}
	SetTargetFPS(140);
	
	registerBlocks();
	registerItems();
	globalGameEngine = nullptr;

	RESOURCE_MANAGER.playMusic("TITLE");
	// load map&level
	Level level1(Map::basePath + "MAP_1.1.json", "BACKGROUND_1", "MUSIC_1", "1-1");
	Level level2(Map::basePath + "MAP_1.2.json", "BACKGROUND_2", "MUSIC_2", "1-2");
	Level level3(Map::basePath + "kmap_3.json", "BACKGROUND_3", "MUSIC_3", "1-3");
	loadedLevel.push_back(&level1);
	loadedLevel.push_back(&level2);
	loadedLevel.push_back(&level3);
	// gui
	loadGUI();

	// map
	selectMap(selectedMap);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexturePro(
			backgroundTexture,
			{ 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height },
			{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
			{ 0, 0 },
			0.0f,
			WHITE);
		if (SETTING.isMusicEnabled())
			UpdateMusicStream(RESOURCE_MANAGER.getMusic("TITLE"));
		if (currentState) {
			currentState->update();
			currentState->draw();
			currentState->handleInput();
		}

		EndDrawing();

	}
	loadedLevel.clear();
	if (globalGameEngine != nullptr) {
		delete globalGameEngine;
		globalGameEngine = nullptr;
	}
	RESOURCE_MANAGER.UnloadAllResources();
	CloseWindow();
	CloseAudioDevice();
}

void Game::setState(std::unique_ptr<MenuState> newState)
{
	currentState = std::move(newState);
}

void Game::configureSettings(bool audioEnabled, bool musicEnabled)
{
	this->audioEnabled = audioEnabled;
	this->musicEnabled = musicEnabled;
}

void Game::selectCharacter(int characterIndex)
{
	this->selectedCharacter = characterIndex;
}

void Game::selectMap(int mapIndex)
{
	if (mapIndex > 3 || mapIndex <= 0)
		return;
		
	switch (mapIndex)
	{
	case 1:
		this->level = loadedLevel[0];
		break;
	case 2:
		this->level = loadedLevel[1];
		break;
	case 3:
		this->level = loadedLevel[2];
		break;
	//case 4:
	//	this->level = loadedLevel[3];
	//	break;
	}
	this->selectedMap = mapIndex;
}

bool Game::isAudioEnabled() const
{
	return audioEnabled;
}

bool Game::isMusicEnabled() const
{
	return musicEnabled;
}

int Game::getSelectedCharacter() const
{
	return selectedCharacter;
}

int Game::getSelectedMap() const
{
	return selectedMap;
}

void Game::saveToConfig(string filename)
{
}

void Game::loadFromConfig(string filename)
{
}

void Game::returnToMainMenu()
{
	setState(std::make_unique<MainMenuState>(this));
}

void Game::setBackground(const std::string& imageName)
{
	if (backgroundTexture.id != 0)
		UnloadTexture(backgroundTexture);
	backgroundTexture = RESOURCE_MANAGER.getTexture(imageName);
	if (backgroundTexture.id == 0)
		throw std::runtime_error("Failed to load background texture: " + imageName);
}

void Game::loadGUI()
{
	GUI::heartTexture = RESOURCE_MANAGER.getTexture("HEART");
	GUI::coinTexture = RESOURCE_MANAGER.getTexture("COIN");
	GUI::multiplicationSign = RESOURCE_MANAGER.getTexture("MSIGN");
	GUI::board = RESOURCE_MANAGER.getTexture("BOARD");
	GUI::board1 = RESOURCE_MANAGER.getTexture("BOARD1");
	GUI::board2 = RESOURCE_MANAGER.getTexture("BOARD2");
	GUI::board3 = RESOURCE_MANAGER.getTexture("BOARD3");
	GUI::largeBoard = RESOURCE_MANAGER.getTexture("LARGE_BOARD");
	GUI::home = RESOURCE_MANAGER.getTexture("HOME_BUTTON");
	GUI::restart = RESOURCE_MANAGER.getTexture("RESTART");
	GUI::setting = RESOURCE_MANAGER.getTexture("SETTING");
	GUI::sound_off = RESOURCE_MANAGER.getTexture("SOUND_OFF");
	GUI::sound_on = RESOURCE_MANAGER.getTexture("SOUND_ON");
}
