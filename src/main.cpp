#include <raylib.h>
#include "../include/Game.h"

int main() {
	InitWindow(1600, 800, "MyMarioGame");
	Game game;
	game.initGame();

	CloseWindow();
	return 0;
}