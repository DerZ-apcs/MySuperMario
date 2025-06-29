#include "../include/Menu.h"
#include "Game.cpp"


MainMenu::MainMenu(Game* game)
{
	this->game = game;
	startButton = { {80, 720}, {0, 0}, ORANGE, DARKGRAY, "Start" };
	continueButton = { {340, 720}, {160, 40}, ORANGE, DARKGRAY, "Continue" };
	settingButton = { {700, 720}, {160, 40}, ORANGE, DARKGRAY, "Setting" };
	charSelectionButton = { {1000, 720}, {200, 40}, ORANGE, DARKGRAY, "Character" };
	mapSelectionButton = { {1390, 720}, {160, 40}, ORANGE, DARKGRAY, "Map" };
}

void MainMenu::init()
{
	InitWindow(1600, 800, "Super Mario");
	InitAudioDevice();
	RESOURCE_MANAGER.LoadAllResources();
	RESOURCE_MANAGER.playMusic("TITLE");
	Texture2D backgroundTexture = RESOURCE_MANAGER.getTexture("MENU_SCREEN");
	SetTargetFPS(140);
	RESOURCE_MANAGER.playMusic("TITLE");
	while (!WindowShouldClose()) {
		update();
		handleInput();
		BeginDrawing();
		ClearBackground(WHITE);
		UpdateMusicStream(RESOURCE_MANAGER.getMusic("TITLE"));
		DrawTexturePro(
			backgroundTexture,
			{ 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height },
			{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
			{ 0, 0 },
			0.0f,
			WHITE);
		draw();
		EndDrawing();
	}
	CloseWindow();
	CloseAudioDevice();
}

void MainMenu::draw()
{
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	charSelectionButton.draw();
	mapSelectionButton.draw();
}

void MainMenu::handleInput()
{
	if (continueButton.isPressed()) {
		if (globalGame == nullptr) {
			game->mario.setPosition({16, 500});
			game->mario.setVel({ 0, 0 });
		}
	}
	else if (startButton.isPressed()) {
		Game game;
		game.initGame();
	}
	
}

void MainMenu::update()
{
	startButton.update();
	continueButton.update();
	settingButton.update();
	charSelectionButton.update();
	mapSelectionButton.update();
}

MainMenu::~MainMenu()
{
	RESOURCE_MANAGER.UnloadAllResources();
}

SettingState::SettingState(Game* game)
{
	audioButton = { {}, {}, ORANGE, DARKGRAY, "Audio"};
	Button musicButton = {};
	Button backButton = {};
}

void SettingState::draw()
{
}

void SettingState::handleInput()
{
}

Button SettingState::audioButton()
{
	return Button();
}

Button SettingState::musicButton()
{
	return Button();
}

Button SettingState::backButton()
{
	return Button();
}

CharSelection::CharSelection(Game* game)
{
}

void CharSelection::draw()
{
}

void CharSelection::handleInput()
{
}

MapSelection::MapSelection(Game* game)
{
}

void MapSelection::draw()
{
}

void MapSelection::handleInput()
{
}

