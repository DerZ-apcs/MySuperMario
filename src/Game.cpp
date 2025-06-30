#include "../include/Game.h"

class MenuState;

Game::Game(): backgroundTexture({0})
{
	currentState = std::make_unique<MainMenuState>(this);
	audioEnabled = true;
	musicEnabled = true;
	player = nullptr;
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
	RESOURCE_MANAGER.LoadAllResources();
	if (backgroundTexture.id == 0) {
		backgroundTexture = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	}
	SetTargetFPS(140);
	globalGameEngine = nullptr;

	RESOURCE_MANAGER.playMusic("TITLE");
	// load level
	Level level1(Map::basePath + "MAP_1.1.json", "BACKGROUND_1", "MUSIC_1", "1-1");
	loadedLevel.push_back(&level1);

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
	if (mapIndex > 4 || mapIndex <= 0)
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
	case 4:
		this->level = loadedLevel[3];
		break;
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
