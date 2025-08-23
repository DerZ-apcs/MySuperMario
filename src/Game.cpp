#include "../include/Game.h"
#include "../include/Level.h"
#include "../include/ItemFactory.h"
#include "../include/BlockFactory.h"

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
	TextButton::SMW = RESOURCE_MANAGER.getFont("SMW");
	if (backgroundTexture.id == 0) {
		backgroundTexture = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	}
	SetTargetFPS(60);
	
	registerBlocks();
	registerItems();
	globalGameEngine = nullptr;
	RESOURCE_MANAGER.playMusic("TITLE");
	// load map&level

	loadedLevel.push_back(std::make_unique<Level>(
		Map::basePath + "kmap_5.json", "BACKGROUND_1", "MUSIC_1", "1-1"));
	loadedLevel.push_back(std::make_unique<Level>(
		Map::basePath + "kmap_2.json", "BACKGROUND_2", "MUSIC_2", "1-2"));
	loadedLevel.push_back(std::make_unique<Level>(
		Map::basePath + "kmap_3.json", "BACKGROUND_3", "MUSIC_3", "1-3"));
	
	// gui
	loadGUI();

	// map
	selectMap(selectedMap);
	level = loadedLevel[0].get();

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
		//RESOURCE_MANAGER.drawAllTiles(); // debug purpose
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
		this->level = loadedLevel[0].get();
		break;
	case 2:
		this->level = loadedLevel[1].get();
		break;
	case 3:
		this->level = loadedLevel[2].get();
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

void Game::loadGUI()
{
	GUI::heartTexture = RESOURCE_MANAGER.getTexture("HEART");
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
	GUI::choosingArrow = RESOURCE_MANAGER.getTexture("choosingArrow");

	GUI::guiTime = RESOURCE_MANAGER.getTexture("guiTime");
	GUI::guiNextitem = RESOURCE_MANAGER.getTexture("guiNextItem");
	GUI::guiCoin = RESOURCE_MANAGER.getTexture("guiCoin");
	GUI::guiClock = RESOURCE_MANAGER.getTexture("guiClock");
	GUI::guiCourseClear = RESOURCE_MANAGER.getTexture("guiCourseClear");
	GUI::gui1Up = RESOURCE_MANAGER.getTexture("gui1Up");
	GUI::gui3Up = RESOURCE_MANAGER.getTexture("gui3Up");
	GUI::guiTimeUp = RESOURCE_MANAGER.getTexture("guiTimeUp");
	GUI::guiLuigiStart = RESOURCE_MANAGER.getTexture("guiLuigiStart");
	GUI::guiMarioStart = RESOURCE_MANAGER.getTexture("guiMarioStart");
	GUI::guiX = RESOURCE_MANAGER.getTexture("guiX");
	GUI::guiLuigi = RESOURCE_MANAGER.getTexture("LuigiGUI");
	GUI::guiMario = RESOURCE_MANAGER.getTexture("MarioGUI");

	GUI::ChoosingMario = RESOURCE_MANAGER.getTexture("SmallMario_Straight");
	GUI::ChoosingLuigi = RESOURCE_MANAGER.getTexture("SmallLuigi_Straight");
	GUI::ChoosingPeach = RESOURCE_MANAGER.getTexture("SmallPeach_Straight");
	GUI::ChoosingMarisa = RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0");
	GUI::ChoosingToad = RESOURCE_MANAGER.getTexture("SmallToad_Straight");
	GUI::GuiP1 = RESOURCE_MANAGER.getTexture("P1GUI");
	GUI::GuiP2 = RESOURCE_MANAGER.getTexture("P2GUI");
	GUI::choosingTextures.push_back(GUI::ChoosingMario);
	GUI::choosingTextures.push_back(GUI::ChoosingLuigi);
	GUI::choosingTextures.push_back(GUI::ChoosingToad);
	GUI::choosingTextures.push_back(GUI::ChoosingPeach);
	GUI::choosingTextures.push_back(GUI::ChoosingMarisa);
}
