#include <raylib.h>
#include "../include/Game.h"

int main() {
	InitWindow(1600, 800, "MyMarioGame");
	InitAudioDevice();
	Game game;
	game.initGame();

	CloseAudioDevice();
	CloseWindow();
	return 0;
}
