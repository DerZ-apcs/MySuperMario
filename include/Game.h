#ifndef GAME_H
#define GAME_H
#include "../include/Menu.h"
#include "../include/Mario.h"
#include "../include/Map.h"
#include "../include/GUI.h"
#include "../include/GameEngine.h"
#include <memory>
#include <utility>
class MenuState;

class Game {
public:
	Game();
	~Game();
	void init();
    void setState(std::unique_ptr<MenuState> newState);

    void configureSettings(bool audioEnabled, bool musicEnabled);
    void selectCharacter(int characterIndex);
    void selectMap(int mapIndex);
    bool isAudioEnabled() const;
    bool isMusicEnabled() const;
    int getSelectedCharacter() const;
    int getSelectedMap() const;
    void saveToConfig(string filename);
    void loadFromConfig(string filename);
    void returnToMainMenu();
    void setBackground(const std::string& imageName);
    void loadGUI();
    Character* player;
    Level* level;

private:
    vector<Level*> loadedLevel;
    bool audioEnabled;
    bool musicEnabled;
    int selectedCharacter;
    int selectedMap = 1;
    std::unique_ptr<MenuState> currentState;
    Texture2D backgroundTexture;
};

#endif