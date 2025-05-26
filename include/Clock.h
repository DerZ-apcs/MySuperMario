#ifndef CLOCK_H
#define CLOCK_H
#include <raylib.h>

class Clock {
private:
	static double lastUpdateTime;
public:
	static double UpdateTimeAcum;
	static void StartTiming();
	static double getDeltaTimeUpdate();
	static void Update();

	static constexpr double FIX_TIME_ST = 1 / 360.0;
};
#endif