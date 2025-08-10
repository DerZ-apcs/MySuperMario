#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
#include "../include/Luigi.h"
#include "../include/Toad.h"
#include "../include/Character.h"
#include "../include/TextButton.h"
#include "../include/GameEngine.h"
#include "../include/EditorEngine.h"
#include "../include/GUI.h"

// forward declaration
class MenuState;
class Game;

class MenuState {
public:
	virtual void draw() = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual ~MenuState() = default;
	void setGame(Game* game) { this->game = game;  }
protected:
	Game* game = nullptr;
};

class MainMenuState : public MenuState {
public:
	explicit MainMenuState(Game* game); 
	void draw() override;
	void handleInput() override;
	void update() override;
	~MainMenuState();
private:
	TextButton startButton;
	TextButton continueButton;
	TextButton saveButton;
	TextButton loadButton;
	TextButton settingButton;
	TextButton mapSelectionButton;
	TextButton modePlayerButton;
	std::vector<int> choosingPosition = { 0, 1, 2, 3, 4, 5, 6 };
	Texture2D guiArrow;
	int currentPosition = 0;
};

class SettingState : public MenuState {
public:
	explicit SettingState(Game* game);
	void draw() override;
	void handleInput() override;

	void update() override;
private:
	TextButton audioButton;
	TextButton musicButton;
	TextButton backButton;
	std::vector<int> choosingPosition = { 0, 1, 2 };
	Texture2D guiArrow;
	int currentPosition = 0;
};

class ModePlayer : public MenuState {
public:
	explicit ModePlayer(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	TextButton singleButton;
	TextButton dualButton;
	TextButton difficultyButton;
	TextButton returnButton;
	std::vector<int> choosingPosition = { 0, 1, 2, 3};
	Texture2D guiArrow;
	int currentPosition = 0;
};

class MapSelection : public MenuState {
public:
	explicit MapSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	TextButton map1Button,
		   map2Button,
		   map3Button;
		//map4Button
	TextButton backButton;
	std::vector<int> choosingPosition = { 0, 1, 2, 3};
	Texture2D guiArrow;
	int currentPosition = 0;
};

class SingleCharSelection : public MenuState {
public:
	explicit SingleCharSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Texture2D selectionBg;
	std::vector<Texture2D> Textures;
	int currentPlayer;
	Texture2D guiP1;
};

class DualCharSelection : public MenuState {
public:
	explicit DualCharSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Texture2D selectionBg;
	std::vector<Texture2D> Textures;
	int currentPlayer1;
	int currentPlayer2;
	Texture2D GuiP1;
	Texture2D GuiP2;
		
};
#endif