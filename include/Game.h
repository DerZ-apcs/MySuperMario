#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "../include/Mario.h"
#include "../include/Clock.h"

class Game {
private:
	int width;
	int height;
	int targetFPS;
	//Color color;
	//Camera2D camera;

	//bool initialize;
	Mario mario;
	Clock clock;
public:
	Game();
	Game(int nwidth, int nheight, int ntargetFPS);

	void init();

	int getWidth();
	int getHeight();
	int getTergetFPS();
	//Color getColor();

	void setWidth(int width);
	void setHeight(int height);
	void setTargetFPS(int targetFPS);
	//void setColor(Color color);
};
#endif