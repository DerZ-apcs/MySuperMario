#include "../include/Menu.h"
#include "../include/Game.h"

MainMenuState::MainMenuState(Game* game)
{
	this->game = game;
	startButton = { Vector2{80, 720}, Vector2{160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Start" };
	continueButton = { {340, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Continue" };
	settingButton = { {700, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Setting" };
	modePlayerButton = { {1000, 720}, {200, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "PlayerMode" }; // for mode
	mapSelectionButton = { {1450, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Map" };
}

void MainMenuState::draw()
{
	startButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	continueButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	mapSelectionButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	modePlayerButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	settingButton.setTexture(RESOURCE_MANAGER.getTexture("BOARD1"));
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	modePlayerButton.draw();
	mapSelectionButton.draw();
}

void MainMenuState::handleInput()
{
	if (continueButton.isPressed()) {
		if (globalGameEngine == nullptr) {
			if (game->multiplayers.empty())
				game->multiplayers.push_back(std::make_unique<Mario>());
			game->multiplayers[0]->setPosition({32, 400});
			game->multiplayers[0]->setVel({ 0, 0 });
			game->multiplayers[0]->setState(FALLING);
			globalGameEngine = new GameEngine(1600, 800, *game->level, &game->multiplayers);
		}
		while (globalGameEngine != nullptr) {
			if (globalGameEngine->run()) {
				delete globalGameEngine;
				globalGameEngine = nullptr;
				if ((game->getSelectedMap() + 1) <= 4)
				{
		/*			if (game->multiplayers.empty())
						game->multiplayers.push_back(std::make_unique<Mario>());*/
					for (auto& p : game->multiplayers) {
						p->setPosition({ 32, 400 });
						p->setVel({ 0, 0 });
						p->setState(FALLING);
					}
					game->selectMap(game->getSelectedMap() + 1);
					globalGameEngine = new GameEngine(1600.0f, 800.0f, *game->level, &game->multiplayers);
				}
				else break;
			}
			else {
				if (globalGameEngine->isOver())
					for (auto& p : game->multiplayers)
						p->reset();
				break;
			}
		}
	}
	else if (startButton.isPressed()) {
		std::cout << "multiplayers size before Start pressed: " << game->multiplayers.size() << "\n";
		if (game->multiplayers.empty()) {
			game->multiplayers.push_back(std::make_unique<Mario>());
			game->multiplayers[0]->setPosition({32, 400});
			game->multiplayers[0]->setVel({0, 0});
			game->multiplayers[0]->setState(FALLING);
		}
		else {
			for (auto& p : game->multiplayers)
				if (p) p->reset();
		}

		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		std::cout << "multiplayers size after Start pressed: " << game->multiplayers.size() << "\n";
		globalGameEngine = new GameEngine(1600, 800, *game->level, &game->multiplayers);

		while (globalGameEngine != nullptr) {
			if (globalGameEngine->run()) {
				auto& players = globalGameEngine->getMultiplayers();
				if (players.empty()) {
					std::cout << "No players found in GameEngine!\n";
					break;
				}
				
				if ((game->getSelectedMap() + 1) <= 4) {
					for (auto& p : players) {
						if (p) {
							p->setPosition({ 16, 400 });
							p->setVel({ 0, 0 });
							p->setState(FALLING);
						}
					}
					//auto movedPlayers = std::move(players);
					delete globalGameEngine;
					globalGameEngine = nullptr;

					game->selectMap(game->getSelectedMap() + 1);
					// Create a new GameEngine with the updated map and players
					globalGameEngine = new GameEngine(1600, 800, *game->level, &game->multiplayers);
				}
				else break;
			}
			else {
				if (globalGameEngine->isOver()) {
					//auto& players = globalGameEngine->getMultiplayers();
					for (auto& p : game->multiplayers)
						p->reset();
				}
				break;
			}
		}
	}
	else if (settingButton.isPressed())
		game->setState(std::make_unique<SettingState>(game));
	else if (modePlayerButton.isPressed())
		game->setState(std::make_unique<ModePlayer>(game));
	else if (mapSelectionButton.isPressed())
		game->setState(std::make_unique<MapSelection>(game));
}

void MainMenuState::update()
{
	startButton.update();
	continueButton.update();
	settingButton.update();
	modePlayerButton.update();
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
}

// Mode player implementation
 
ModePlayer::ModePlayer(Game* game)
{
	this->game = game;
	singleButton = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Single" };
	dualButton = { {400, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Dual" };
	difficultyButton = { {700, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Difficulty" };
	returnButton = { {1000, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Return to Main Menu" };
}

void ModePlayer::draw()
{
	singleButton.draw();
	dualButton.draw();
	difficultyButton.draw();
	returnButton.draw();
}

void ModePlayer::handleInput()
{
	if (singleButton.isPressed())
		game->setState(make_unique<SingleCharSelection>(game));
	else if (dualButton.isPressed())
		game->setState(make_unique<DualCharSelection>(game));
	else if (difficultyButton.isPressed()) {
		
	}
	else if (returnButton.isPressed()) {
		game->returnToMainMenu();
	}
}

void ModePlayer::update()
{
	singleButton.update();
	dualButton.update();
	difficultyButton.update();
	returnButton.update();
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
		for (auto& p : game->multiplayers)
			p->reset();
		game->returnToMainMenu();
	}
	else if (map2Button.isPressed()) {
		game->selectMap(2);
		for (auto& p : game->multiplayers)
			p->reset();
		game->returnToMainMenu();
	}
	else if (map3Button.isPressed()) {
		game->selectMap(3);
		for (auto& p : game->multiplayers)
			p->reset();
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

SingleCharSelection::SingleCharSelection(Game* game)
{
	this->game = game;
	MarioButton = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Mario" };
	LuigiButton = { {500, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Luigi" };
	BackButton = { {900, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Return to Mode Player" };
}

void SingleCharSelection::draw()
{
	MarioButton.draw();
	LuigiButton.draw();
	BackButton.draw();
}

void SingleCharSelection::handleInput()
{
	if (MarioButton.isPressed()) {
		game->multiplayers.clear();

		game->multiplayers.push_back(std::make_unique<Mario>());
		
		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
	else if (LuigiButton.isPressed()) {
		game->multiplayers.clear();
		game->multiplayers.push_back(std::make_unique<Luigi>());
		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
	else if (BackButton.isPressed())
		game->returnToMainMenu();
}

void SingleCharSelection::update()
{
	MarioButton.update();
	LuigiButton.update();
	BackButton.update();
}

DualCharSelection::DualCharSelection(Game* game)
{
	this->game = game;
	currentPlayer1 = 0;
	currentPlayer2 = 0;
	textureP1 = RESOURCE_MANAGER.getTexture("SmallMario_RIGHT_0");
	textureP2 = RESOURCE_MANAGER.getTexture("SmallLuigi_RIGHT_0");
	Textures.push_back(textureP1);
	Textures.push_back(textureP2);
	guiMario = RESOURCE_MANAGER.getTexture("MarioGUI");
	guiLuigi = RESOURCE_MANAGER.getTexture("LuigiGUI");
	white = RESOURCE_MANAGER.getTexture("WHITE");
	sea = RESOURCE_MANAGER.getTexture("BACKGROUND_8");
}

void DualCharSelection::draw()
{
	// background
	DrawTexturePro(white, { 0, 0, (float)white.width, (float)white.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(sea, { 0, 0, (float)sea.width, (float)sea.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
	
	// gui1
	if (currentPlayer1 == 0) {
		DrawTexturePro(guiMario, { 0, 0, (float)guiMario.width, (float)guiMario.height },
			{ 330, 200, 320, 64 }, { 0, 0 }, 0.f, WHITE);
	} else DrawTexturePro(guiLuigi, { 0, 0, (float)guiLuigi.width, (float)guiLuigi.height },
		{ 330, 200, 320, 64 }, { 0, 0 }, 0.f, WHITE);
	
	// gui2
	if (currentPlayer2 == 0)
		DrawTexturePro(guiMario, { 0, 0, (float)guiMario.width, (float)guiMario.height },
		{ 930, 200, 320, 64 }, { 0, 0 }, 0.f, WHITE);
	else DrawTexturePro(guiLuigi, { 0, 0, (float)guiLuigi.width, (float)guiLuigi.height },
		{ 930, 200, 320, 64 }, { 0, 0 }, 0.f, WHITE);
	
	// texture 1 & 2
	DrawTexturePro(textureP1, { 0, 0, (float)textureP1.width, (float)textureP1.height }, 
		{400, 300, 32 * 5, 40 * 5}, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(textureP2, { 0, 0, (float)textureP2.width, (float)textureP2.height }, 
		{1000, 300, 32 * 5, 40 * 5}, { 0, 0 }, 0.f, WHITE);
}

void DualCharSelection::handleInput()
{
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
		currentPlayer1++;
		if (currentPlayer1 > 1) currentPlayer1 = 0;
	}
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
		currentPlayer2++;
		if (currentPlayer2 > 1) currentPlayer2 = 0;
	}
	textureP1 = Textures[currentPlayer1];
	textureP2 = Textures[currentPlayer2];

	if (IsKeyPressed(KEY_ENTER)) {
		// init the game with 2 players
		game->multiplayers.clear();

		if (currentPlayer1 == 0) {
			game->multiplayers.push_back(std::make_unique<Mario>());
		}
		else game->multiplayers.push_back(std::make_unique<Luigi>());

		if (currentPlayer2 == 0) {
			game->multiplayers.push_back(std::make_unique<Mario>());
		}
		else game->multiplayers.push_back(std::make_unique<Luigi>());

		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
}

void DualCharSelection::update()
{
}
