#include <raylib.h>
#include "../include/Game.h"

int main() {
	InitWindow(1600, 800, "MyMarioGame");
	InitAudioDevice();
	Game game;
	game.initGame();

	/*auto& resourceManager = Singleton<ResourceManager>::getInstance();
	resourceManager.LoadAllResources();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexture(resourceManager.getTexture("BACKGROUND_1"), 0, 0, WHITE);
		EndDrawing();
	}
	resourceManager.UnloadAllResources();*/
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
