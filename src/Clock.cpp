#include "../include/Clock.h"
double Clock::lastUpdateTime = 0.0;
double Clock::UpdateTimeAcum = 0.0;

void Clock::StartTiming()
{
	lastUpdateTime = GetTime();
}

double Clock::getDeltaTimeUpdate()
{
	return GetTime() - lastUpdateTime;
}

void Clock::Update()
{
	lastUpdateTime = GetTime();
}
