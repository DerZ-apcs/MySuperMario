#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
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
	Button charSelectionButton;
	Button mapSelectionButton;
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

class CharSelection : public MenuState {
public:
	explicit CharSelection(Game* game);
	void draw() override;
	void handleInput() override;
	void update() override;
private:
	Button MarioButton;
	Button LuigiButton;
	Button backButton;
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
		map3Button,
		map4Button;
	Button backButton;
};

#endif