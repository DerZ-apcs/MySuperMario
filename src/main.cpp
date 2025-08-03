#include <raylib.h>
#include "../include/Game.h"


int main() {
	Game game;
	game.init();

	return 0;
}

//#include "raylib.h"
//#include <iostream>
//
//int main() {
//    InitWindow(800, 600, "SMW Font Test");
//
//    // Load the uploaded SMW.ttf font
//    Font smwFont = LoadFontEx("resources/Font/SMW.ttf", 64, nullptr, 0);
//
//    // Confirm it's valid
//    if (smwFont.glyphCount == 0 || smwFont.glyphs == nullptr || smwFont.texture.id == 0) {
//        std::cerr << "[ERROR] SMW.ttf failed to load!" << std::endl;
//        CloseWindow();
//        return -1;
//    }
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(DARKGRAY);
//        DrawTextEx(smwFont, "Hello, Mario World!", { 100, 100 }, 48, 1, WHITE);
//        EndDrawing();
//    }
//
//    CloseWindow();
//    return 0;
//}
