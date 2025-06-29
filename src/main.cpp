#include <raylib.h>
#include "../include/Game.h"
#include "../include/Menu.h"


int main() {
	/*InitWindow(1600, 800, "MyMarioGame");
	InitAudioDevice();
	Game game;
	game.initGame();

	CloseAudioDevice();
	CloseWindow();*/
	MainMenu menu;
	menu.init();

	return 0;
}
