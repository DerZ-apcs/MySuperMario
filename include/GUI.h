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

	static void drawStatusBar(const Character* player);
	static void drawPauseMenu();
	static void drawLevelClear();
	static void drawDeathScreen();
	static void drawGameOverScreen();
};

#endif