#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
#include "../include/Luigi.h"
#include "../include/Character.h"
#include "../include/Button.h"
#include "../include/GameEngine.h"
#include "../include/GUI.h"

// forward declaration
class MenuState;
class Game;

class MenuState: public Button {
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
	Button startButton;
	Button continueButton;
	Button settingButton;
	Button mapSelectionButton;
	Button modePlayerButton;
};

class SettingState : public MenuState {
public:
	explicit SettingState(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Button audioButton;
	Button musicButton;
	Button backButton;
};

class ModePlayer : public MenuState {
public:
	explicit ModePlayer(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Button singleButton;
	Button dualButton;
	Button difficultyButton; 
	Button returnButton;
};

class MapSelection : public MenuState {
public:
	explicit MapSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Button map1Button,
		   map2Button,
		   map3Button;
		//map4Button
	Button backButton;
};

class SingleCharSelection : public MenuState {
public:
	explicit SingleCharSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Button MarioButton;
	Button LuigiButton;
	Button BackButton;
};

class DualCharSelection : public MenuState {
public:
	explicit DualCharSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Texture2D white, sea;
	std::vector<Texture2D> Textures;
	int currentPlayer1;
	int currentPlayer2;
	Texture2D textureP1;
	Texture2D textureP2;
	Texture2D guiMario, guiLuigi;
};
#endif