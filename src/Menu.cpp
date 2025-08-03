#include "../include/Menu.h"
#include "../include/Game.h"

MainMenuState::MainMenuState(Game* game)
{
	this->game = game;
	startButton = { Vector2{400, 300}, Vector2{160, 80}, "Start" };
	continueButton = { {400, 360}, {160, 80}, "Continue" };
	settingButton = { {400, 420}, {160, 80}, "Setting" };
	modePlayerButton = { {400, 480}, {200, 80}, "Mode" }; // for mode
	mapSelectionButton = { {400, 540}, {160, 80}, "Map" };
	guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
}

void MainMenuState::draw()
{
	startButton.draw();
	continueButton.draw();
	settingButton.draw();
	modePlayerButton.draw();
	mapSelectionButton.draw();
	if (guiArrow.id == 0)
		guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
	DrawTexturePro(guiArrow, { 0, 0, (float)guiArrow.width, (float)guiArrow.height },
		{ 330, (float)305 + currentPosition * 60, (float)guiArrow.width, (float)guiArrow.height }, { 0, 0 }, 0.f, WHITE);
}

void MainMenuState::handleInput()
{
	if (IsKeyPressed(KEY_UP)) {
		currentPosition--;
		if (currentPosition < 0) currentPosition = choosingPosition.size() - 1; // wrap around to last position
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		currentPosition++;
		if (currentPosition >= choosingPosition.size()) currentPosition = 0; // wrap around to first position
	}

	if (continueButton.isPressed() || (currentPosition == 0 && IsKeyPressed(KEY_ENTER))) {
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
	else if (startButton.isPressed() || (currentPosition == 1 && IsKeyPressed(KEY_ENTER))) {
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
	else if (settingButton.isPressed() || (currentPosition == 2 && IsKeyPressed(KEY_ENTER)))
		game->setState(std::make_unique<SettingState>(game));
	else if (modePlayerButton.isPressed() || (currentPosition == 3 && IsKeyPressed(KEY_ENTER)))
		game->setState(std::make_unique<ModePlayer>(game));
	else if (mapSelectionButton.isPressed()|| (currentPosition == 4 && IsKeyPressed(KEY_ENTER)))
		game->setState(std::make_unique<MapSelection>(game));
}

void MainMenuState::update()
{
	startButton.update();
	continueButton.update();
	settingButton.update();
	modePlayerButton.update();
	mapSelectionButton.update();
	if (currentPosition == 0) startButton.setHovered(true);
	else startButton.setHovered(false);
	if (currentPosition == 1) continueButton.setHovered(true);
	else continueButton.setHovered(false);
	if (currentPosition == 2) settingButton.setHovered(true);
	else settingButton.setHovered(false);
	if (currentPosition == 3) modePlayerButton.setHovered(true);
	else modePlayerButton.setHovered(false);
	if (currentPosition == 4) mapSelectionButton.setHovered(true);
	else mapSelectionButton.setHovered(false);
}

MainMenuState::~MainMenuState()
{

}

// SettingState implementation
SettingState::SettingState(Game* game) { 
	this->game = game; 
	audioButton = { {400, 300}, {160, 80}, "Sound: ON" };
	musicButton = { {400, 360}, {160, 80}, "Music: ON" };
	backButton = { {400, 420}, {160, 80}, "Return" };
	guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
}


void SettingState::draw()
{
	audioButton.draw();
	musicButton.draw();
	backButton.draw();
	if (guiArrow.id == 0)
		guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
	DrawTexturePro(guiArrow, { 0, 0, (float)guiArrow.width, (float)guiArrow.height },
		{ 330, (float)305 + currentPosition * 60, (float)guiArrow.width, (float)guiArrow.height }, { 0, 0 }, 0.f, WHITE);
}

void SettingState::handleInput()
{
	if (audioButton.isPressed() || (currentPosition == 0 && IsKeyPressed(KEY_ENTER))) {
		if (SETTING.isSoundEnabled())
			audioButton.setText("Sound: OFF");
		else audioButton.setText("Sound: ON");
		SETTING.setSound(!game->isAudioEnabled());
		game->configureSettings(!game->isAudioEnabled(), game->isMusicEnabled());
	} 
	else if (musicButton.isPressed() || (currentPosition == 1 && IsKeyPressed(KEY_ENTER))) {
		if (SETTING.isMusicEnabled())
			musicButton.setText("Music: OFF");
		else musicButton.setText("Music: ON");
		SETTING.setMusic(!game->isMusicEnabled());
		game->configureSettings(game->isAudioEnabled(), !game->isMusicEnabled());
	}
	else if (backButton.isPressed()|| (currentPosition == 2 && IsKeyPressed(KEY_ENTER))) {
		game->returnToMainMenu();
	}
	if (IsKeyPressed(KEY_UP)) {
		currentPosition--;
		if (currentPosition < 0) currentPosition = 2; // wrap around to last position
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		currentPosition++;
		if (currentPosition >= 3) currentPosition = 0; // wrap around to first position
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
	if (currentPosition == 0) audioButton.setHovered(true);
	else audioButton.setHovered(false);
	if (currentPosition == 1) musicButton.setHovered(true);
	else musicButton.setHovered(false);
	if (currentPosition == 2) backButton.setHovered(true);
	else backButton.setHovered(false);
}

// Mode player implementation
 
ModePlayer::ModePlayer(Game* game)
{
	this->game = game;
	singleButton = { {400, 300}, {160, 80}, "Single" };
	dualButton = { {400, 360}, {160, 80}, "Dual" };
	difficultyButton = { {400, 420}, {160, 80}, "Difficulty" };
	returnButton = { {400, 480}, {160, 80}, "Return" };
	guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
}

void ModePlayer::draw()
{
	singleButton.draw();
	dualButton.draw();
	difficultyButton.draw();
	returnButton.draw();
	if (guiArrow.id == 0)
		guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
	DrawTexturePro(guiArrow, { 0, 0, (float)guiArrow.width, (float)guiArrow.height },
		{ 330, (float)305 + currentPosition * 60, (float)guiArrow.width, (float)guiArrow.height }, { 0, 0 }, 0.f, WHITE);
}

void ModePlayer::handleInput()
{
	if (singleButton.isPressed() || (currentPosition == 0 && IsKeyPressed(KEY_ENTER)))
		game->setState(make_unique<SingleCharSelection>(game));
	else if (dualButton.isPressed() || (currentPosition == 1 && IsKeyPressed(KEY_ENTER)))
		game->setState(make_unique<DualCharSelection>(game));
	else if (difficultyButton.isPressed()) {
		
	}
	else if (returnButton.isPressed() || (currentPosition == 2 && IsKeyPressed(KEY_ENTER))) {
		game->returnToMainMenu();
	}
	if (IsKeyPressed(KEY_UP)) {
		currentPosition--;
		if (currentPosition < 0) currentPosition = 3; // wrap around to last position
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		currentPosition++;
		if (currentPosition >= 4) currentPosition = 0; // wrap around to first position
	}
}

void ModePlayer::update()
{
	singleButton.update();
	dualButton.update();
	difficultyButton.update();
	returnButton.update();
	if (currentPosition == 0) singleButton.setHovered(true);
	else singleButton.setHovered(false);
	if (currentPosition == 1) dualButton.setHovered(true);
	else dualButton.setHovered(false);
	if (currentPosition == 2) difficultyButton.setHovered(true);
	else difficultyButton.setHovered(false);
	if (currentPosition == 3) returnButton.setHovered(true);
	else returnButton.setHovered(false);
}

//MapSelection Implementation

MapSelection::MapSelection(Game* game)
{
	this->game = game;
	map1Button = { {400, 300}, {160, 80}, "MAP 1" };
	map2Button = { {400, 360}, {160, 80}, "MAP 2" };
	map3Button = { {400, 420}, {160, 80}, "MAP 3" };
	backButton = { {400, 480}, {160, 80}, "Return" };
	guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
}

void MapSelection::draw()
{
	map1Button.draw();
	map2Button.draw();
	map3Button.draw();
	backButton.draw();
	if (guiArrow.id == 0)
		guiArrow = RESOURCE_MANAGER.getTexture("choosingArrow");
	DrawTexturePro(guiArrow, { 0, 0, (float)guiArrow.width, (float)guiArrow.height },
		{ 330, (float)305 + currentPosition * 60, (float)guiArrow.width, (float)guiArrow.height }, { 0, 0 }, 0.f, WHITE);
}

void MapSelection::handleInput()
{
	if (map1Button.isPressed() || (currentPosition == 0 && IsKeyPressed(KEY_ENTER))) {
		game->selectMap(1);
		for (auto& p : game->multiplayers)
			p->reset();
		game->returnToMainMenu();
	}
	else if (map2Button.isPressed() || (currentPosition == 1 && IsKeyPressed(KEY_ENTER))) {
		game->selectMap(2);
		for (auto& p : game->multiplayers)
			p->reset();
		game->returnToMainMenu();
	}
	else if (map3Button.isPressed() || (currentPosition == 2 && IsKeyPressed(KEY_ENTER))) {
		game->selectMap(3);
		for (auto& p : game->multiplayers)
			p->reset();
		game->returnToMainMenu();
	}
	else if (backButton.isPressed() || (currentPosition == 1 && IsKeyPressed(KEY_ENTER)))
		game->returnToMainMenu();

	if (IsKeyPressed(KEY_UP)) {
		currentPosition--;
		if (currentPosition < 0) currentPosition = 3; // wrap around to last position
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		currentPosition++;
		if (currentPosition >= 4) currentPosition = 0; // wrap around to first position
	}
}

void MapSelection::update()
{
	map1Button.update();
	map2Button.update();
	map3Button.update();
	backButton.update();
	if (currentPosition == 0) map1Button.setHovered(true);
	else map1Button.setHovered(false);
	if (currentPosition == 1) map2Button.setHovered(true);
	else map2Button.setHovered(false);
	if (currentPosition == 2) map3Button.setHovered(true);
	else map3Button.setHovered(false);
	if (currentPosition == 3) backButton.setHovered(true);
	else backButton.setHovered(false);
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
