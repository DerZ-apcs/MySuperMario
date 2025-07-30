#ifndef SETTING_H
#define SETTING_H
#include <../include/Singleton.h>

class Setting {
	template <class T>
	friend class Singleton;
private:
	float screenWidth;
	float screenHeight;
	float scale;
	bool fullscreen; // fullscreen on/off
	bool sound; // sound effect on/off
	bool music; // music on/off
	bool isdebugMode = false;
	Setting() {};
	Setting(const Setting& other) = delete;
	Setting& operator=(const Setting& other) = delete;
public:
	~Setting() = default;
	// getter
	int getScreenWidth() const;
	int getScreenHeight() const;
	int getScale() const;
	bool isFullScreen() const;
	bool isSoundEnabled() const;
	bool isMusicEnabled() const;

	// setter
	void setScreenWidth(float width);
	void setScreenHeight(float height);
	void setScale(float scale);
	void setFullScreen(bool isFullscreen);
	void setSound(bool isEnabled);
	void setMusic(bool isEnabled);
	void resetToDefaults();

	void setDebugMode(bool isDebug) {
		this->isdebugMode = isDebug;
	}
	bool getDebugMode() const {
		return isdebugMode;
	}

};

#endif