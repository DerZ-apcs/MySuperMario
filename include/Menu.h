#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
#include "../include/Button.h"
#include "../include/Game.h"

// forward declaration
//class MenuState;

class MenuState: public Button {
public:
	virtual void draw() = 0;
	virtual void handleInput() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	void setGame(Game* game) { this->game = game;  }
protected:
	Game* game = nullptr;
};

class MainMenu : public MenuState {
public:
	explicit MainMenu(Game* game); 
	void init() override;
	void draw() override;
	void handleInput() override;
	void update() override;
	~MainMenu();
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
private:
	Button map1Button,
		map2Button,
		map3Button,
		map4Button;
	Button backButton;
};

#endif