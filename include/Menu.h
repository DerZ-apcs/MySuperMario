#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "../include/Mario.h"
#include "../include/Button.h"

// forward declaration
class MenuState;

class Menu {

};
class MenuState: public Button {
public:
	virtual void draw() = 0;
	virtual void handleInput() = 0;
protected:
	Menu* menu = nullptr;
};

class MainMenu : public MenuState {
public:
	MainMenu();
	void draw() override;
	void handleInput() override;
private:
	Button startButton;
	Button continueButton;
	Button settingButton;
	Button charSelectionButton;
	Button mapSelectionButton;
};

class SettingState : public MenuState {
public:
	SettingState();
	void draw() override;
	void handleInput() override;
private:
	Button audioButton();
	Button musicButton();
	Button backButton();
};

class CharSelection : public MenuState {
public:
	CharSelection();
	void draw() override;
	void handleInput() override;
private:
	Button MarioButton;
	Button LuigiButton;
	Button backButton;
};

class MapSelection : public MenuState {
public:
	MapSelection();
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