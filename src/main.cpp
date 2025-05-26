#include <raylib.h>
#include "../include/Mario.h"
#include "../include/Clock.h"
#include "../include/ResourceManager.h"
#include <iostream>

int main() {
	InitWindow(1600, 800, "MyMarioGame");
	SetTargetFPS(140);
	Clock clock;
	Mario mario;
	ResourceManager::LoadAllResources();
	clock.StartTiming();
	while (!WindowShouldClose()) {
		clock.UpdateTimeAcum += GetFrameTime();
		while (clock.UpdateTimeAcum >= clock.FIX_TIME_ST) {
			mario.Update();
			clock.Update();
			if (clock.getDeltaTimeUpdate() == 0) {
				clock.UpdateTimeAcum -= clock.FIX_TIME_ST;
			}
			clock.UpdateTimeAcum -= clock.getDeltaTimeUpdate();
		}
		BeginDrawing();
		ClearBackground(WHITE);
		mario.draw();
		EndDrawing();

	}
	ResourceManager::UnloadAllResources();
	CloseWindow();
	return 0;
}