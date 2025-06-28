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

	
	//std::string path = "resources/images/tiles/AllTiles/tile_99.png";
	//Texture2D tt = LoadTexture(path.c_str());
	//DrawTexture(tt, 50, 50, WHITE);
	//std::filesystem::path fullPath = std::filesystem::absolute(path);
	//std::cout << fullPath << std::endl;

	CloseAudioDevice();
	CloseWindow();
	return 0;
}
