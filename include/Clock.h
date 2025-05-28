#ifndef CLOCK_H
#define CLOCK_H
#include <raylib.h>

class Clock {
private:
	//static constexpr double lastUpdateTime;
	static constexpr double FIX_TIME_ST = 1 / 360.0;

public:
	static double UpdateTimeAcum;
	//static void StartTiming();
	static double getDeltaTimeUpdate();
	//static void Update();

};
#endif