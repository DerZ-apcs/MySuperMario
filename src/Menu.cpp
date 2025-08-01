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
	audioButton = { {100, 720}, {160, 80}, RESOURCE_MANAGER.getTexture("BOARD1"), "Sound: ON" };
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

	if (SETTING.isSoundEnabled() && audioButton.getText() == "Sound: OFF")
		audioButton.setText("Sound: ON");
	else if (!SETTING.isSoundEnabled() && audioButton.getText() == "Sound: ON")
		audioButton.setText("Sound: OFF");

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
	currentPlayer = 0;
	
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallMario_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallLuigi_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallToad_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallPeach_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0"));
	guiP1 = RESOURCE_MANAGER.getTexture("P1GUI");
	selectionBg = RESOURCE_MANAGER.getTexture("SelectionBackground");
}

void SingleCharSelection::draw()
{
	// background
	if (selectionBg.id == 0)
		cout << "Cannot load selection bg" << endl;
	else DrawTexturePro(selectionBg, { 0, 0, (float)selectionBg.width, (float)selectionBg.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
	// gui1
	// draw 4 texture of character

	DrawTexturePro(Textures[0], { 0, 0, (float)Textures[0].width, (float)Textures[0].height },
		{ 270, 500 - 24, 32 * 4, 46 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[1], { 0, 0, (float)Textures[1].width, (float)Textures[1].height },
		{ 270 + (float)1 * 225, 500 - 40, 32 * 4, 50 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[2], { 0, 0, (float)Textures[2].width, (float)Textures[2].height },
		{ 270 + (float)2 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[3], { 0, 0, (float)Textures[3].width, (float)Textures[3].height },
		{ 270 + (float)3 * 225, 500 - 32, 32 * 4, 48 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[4], { 0, 0, (float)Textures[4].width, (float)Textures[4].height },
		{ 270 + (float)4 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE);

	DrawTexturePro(guiP1, { 0, 0, (float)guiP1.width, (float)guiP1.height }, { 280 + (float)currentPlayer * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
}

void SingleCharSelection::handleInput()
{
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
		currentPlayer--;
		if (currentPlayer < 0) currentPlayer = 4; // wrap around to last player
	}
	else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
		currentPlayer++;
		if (currentPlayer > 4) currentPlayer = 0; // wrap around to first player
	}
	
	if (IsKeyPressed(KEY_ENTER)) {
		// init the game with 1 player
		game->multiplayers.clear();

		if (currentPlayer == 0) {
			game->multiplayers.push_back(std::make_unique<Mario>());
		}
		else if (currentPlayer == 1)
			game->multiplayers.push_back(std::make_unique<Luigi>());
		else if (currentPlayer == 2)
			game->multiplayers.push_back(std::make_unique<Toad>());
		else if (currentPlayer == 3)
			game->multiplayers.push_back(std::make_unique<Peach>());
		else if (currentPlayer == 4)
			game->multiplayers.push_back(std::make_unique<Marisa>());

		if (globalGameEngine != nullptr) {
			delete globalGameEngine;
			globalGameEngine = nullptr;
		}
		game->returnToMainMenu();
	}
}

void SingleCharSelection::update()
{

}

DualCharSelection::DualCharSelection(Game* game)
{
	this->game = game;
	currentPlayer1 = 0;
	currentPlayer2 = 0;
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallMario_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallLuigi_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallToad_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallPeach_Straight"));
	Textures.push_back(RESOURCE_MANAGER.getTexture("SmallMarisa_RIGHT_0"));
	GuiP1 = RESOURCE_MANAGER.getTexture("P1GUI");
	GuiP2 = RESOURCE_MANAGER.getTexture("P2GUI");
	selectionBg = RESOURCE_MANAGER.getTexture("SelectionBackground");
}

void DualCharSelection::draw()
{
	// background
	DrawTexturePro(selectionBg, { 0, 0, (float)selectionBg.width, (float)selectionBg.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
	// gui1
	// draw 4 texture of character

	DrawTexturePro(Textures[0], { 0, 0, (float)Textures[0].width, (float)Textures[0].height },
		{ 270, 500 - 24, 32 * 4, 46 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[1], { 0, 0, (float)Textures[1].width, (float)Textures[1].height },
		{ 270 + (float)1 * 225, 500 - 40, 32 * 4, 50 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[2], { 0, 0, (float)Textures[2].width, (float)Textures[2].height },
		{ 270 + (float)2 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[3], { 0, 0, (float)Textures[3].width, (float)Textures[3].height },
		{ 270 + (float)3 * 225, 500 - 32, 32 * 4, 48 * 4 }, { 0, 0 }, 0.f, WHITE);
	DrawTexturePro(Textures[4], { 0, 0, (float)Textures[4].width, (float)Textures[4].height },
		{ 270 + (float)4 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE);

	if (currentPlayer1 == currentPlayer2) {
		DrawTexturePro(GuiP1, { 0, 0, (float)GuiP1.width, (float)GuiP1.height }, { 280 + (float)currentPlayer1 * 225 - 30, 350, 75, 105}, { 0, 0 }, 0.f, WHITE);
		DrawTexturePro(GuiP2, { 0, 0, (float)GuiP2.width, (float)GuiP2.height }, { 280 + (float)currentPlayer2 * 225 + 55, 350, 75, 105}, { 0, 0 }, 0.f, WHITE);

	}
	else {
		DrawTexturePro(GuiP1, { 0, 0, (float)GuiP1.width, (float)GuiP1.height }, { 280 + (float)currentPlayer1 * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
		DrawTexturePro(GuiP2, { 0, 0, (float)GuiP2.width, (float)GuiP2.height }, { 280 + (float)currentPlayer2 * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
	}
}

void DualCharSelection::handleInput()
{
	if (IsKeyPressed(KEY_A)) {
		currentPlayer1--;
		if (currentPlayer1 < 0) currentPlayer1 = 4;
	}
	else if (IsKeyPressed(KEY_D)) {
		currentPlayer1++;
		if (currentPlayer1 > 4) currentPlayer1 = 0;
	}

	if (IsKeyPressed(KEY_LEFT)) {
		currentPlayer2--;
		if (currentPlayer2 < 0) currentPlayer2 = 4;
	}
	else if (IsKeyPressed(KEY_RIGHT)) {
		currentPlayer2++;
		if (currentPlayer2 > 4) currentPlayer2 = 0;
	}

	if (IsKeyPressed(KEY_ENTER)) {
		// init the game with 2 players
		game->multiplayers.clear();

		if (currentPlayer1 == 0) {
			game->multiplayers.push_back(std::make_unique<Mario>());
		}
		else if (currentPlayer1 == 1)
			game->multiplayers.push_back(std::make_unique<Luigi>());
		else if (currentPlayer1 == 2)
			game->multiplayers.push_back(std::make_unique<Toad>());
		else if (currentPlayer1 == 3)
			game->multiplayers.push_back(std::make_unique<Peach>());
		else if (currentPlayer1 == 4)
			game->multiplayers.push_back(std::make_unique<Marisa>());


		if (currentPlayer2 == 0) {
			game->multiplayers.push_back(std::make_unique<Mario>());
		}
		else if (currentPlayer2 == 1)
			game->multiplayers.push_back(std::make_unique<Luigi>());
		else if (currentPlayer2 == 2)
			game->multiplayers.push_back(std::make_unique<Toad>());
		else if (currentPlayer2 == 3)
			game->multiplayers.push_back(std::make_unique<Peach>());
		else if (currentPlayer2 == 4)
			game->multiplayers.push_back(std::make_unique<Marisa>());

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
