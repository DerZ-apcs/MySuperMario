#ifndef GUI_H
#define GUI_H
#include <raylib.h>
#include "../include/Global.h"

using namespace std;

class Character;

//Static class to draw GUI using raylib
class GUI {
public:
	static Texture2D heartTexture;
	static Texture2D coinTexture;
	static Texture2D multiplicationSign;
	static Texture2D board;
	static Texture2D largeBoard;
	static Texture2D board1;
	static Texture2D board2;
	static Texture2D board3;
	static Texture2D restart;
	static Texture2D home;
	static Texture2D setting;
	static Texture2D sound_on;
	static Texture2D sound_off;
	static Texture2D choosingArrow;
	static Texture2D guiTime;
	static Texture2D guiNextitem;
	static Texture2D guiCoin;
	static Texture2D guiClock;
	static Texture2D guiCourseClear;
	static Texture2D gui1Up;
	static Texture2D gui3Up;
	static Texture2D guiTimeUp;
	static Texture2D guiLuigiStart;
	static Texture2D guiMarioStart;
	static Texture2D guiX;
	static Texture2D guiLuigi;
	static Texture2D guiMario;

	static void drawPlayerStatus(const Character* player, Vector2 origin);
	static void drawStatusBar(const Character* player);
	static void drawStatusBar(std::vector<std::unique_ptr<Character>>& multiplayers);
	static void drawPauseMenu();
	static void drawLevelClear();
	static void drawVictory();
	static void drawTransitioningBetweenMap();
	static void drawDeathScreen();
	static void drawGameOverScreen();
	static void drawNumber(int number, Vector2 position, float spacing = 10.f);
	static void drawSmallNumber(int number, Vector2 position, float spacing = 5.f);
	static void drawYellowNumber(int number, Vector2 position, float spacing = 5.f);
	static bool home_is_pressed;
	static bool restart_is_pressed;
	static bool sound_is_pressed;
	static bool setting_is_pressed;
};

#endif