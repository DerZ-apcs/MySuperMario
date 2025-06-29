#include "../include/Game.h"

class MenuState;

Game::Game(): backgroundTexture({0})
{
	//RESOURCE_MANAGER.LoadAllResources();
	currentState = std::make_unique<MainMenuState>(this);
	audioEnabled = true;
	musicEnabled = true;
	player = nullptr;
	map = nullptr;
	selectedCharacter = 1;
	selectedMap = 1;
}

Game::~Game()
{
	if (backgroundTexture.id != 0) {
		UnloadTexture(backgroundTexture);
		backgroundTexture.id = 0;
	}
	//RESOURCE_MANAGER.UnloadAllResources();
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

	RESOURCE_MANAGER.playMusic("TITLE");
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
		//if (SETTING.isMusicEnabled())
			UpdateMusicStream(RESOURCE_MANAGER.getMusic("TITLE"));
		if (currentState) {
			currentState->draw();
			currentState->update();
			currentState->handleInput();
		}
		EndDrawing();
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
		
	this->map = loadedLevel[static_cast<std::vector<Map*, std::allocator<Map*>>::size_type>(mapIndex) - 1];
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
