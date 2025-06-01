#include "../include/Setting.h"

int Setting::getScreenWidth() const
{
	return screenWidth;
}

int Setting::getScreenHeight() const
{
	return screenHeight;
}

int Setting::getScale() const
{
	return scale;
}

bool Setting::isFullScreen() const
{
	return fullscreen;
}

bool Setting::isSoundEnabled() const
{
	return sound;
}

bool Setting::isMusicEnabled() const
{
	return music;
}

void Setting::setScreenWidth(float width)
{
	this->screenWidth = width;
}

void Setting::setScreenHeight(float height)
{
	this->screenHeight = height;
}

void Setting::setScale(float scale)
{
	this->scale = scale;
}

void Setting::setFullScreen(bool isFullscreen)
{
	this->fullscreen = isFullscreen;
}

void Setting::setSound(bool isEnabled)
{
	this->sound = isEnabled;
}

void Setting::setMusic(bool isEnabled)
{
	this->music = isEnabled;
}

void Setting::resetToDefaults()
{
	screenWidth = 1280;
	screenHeight = 800;
	scale = 1;
	fullscreen = false;
	sound = true;
	music = true;
}
